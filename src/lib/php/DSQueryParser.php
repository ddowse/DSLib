<?php

require_once "DSLib.php";
require_once "DSClassInfo.php";

define("DS_QUERY_PARSER_VERSION", "0.0.1");
define("DS_QUERY_PARSER_NAME",    "DSQueryParser");
define("DS_QUERY_PARSER_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSQueryParser extends DSLib {

	protected $query       = "";
	protected $keyValues   = array();
	protected $fields      = array();
	protected $storeResult = false;

	public function __construct($query = "") {
		parent::__construct();
		$this->query = $query;
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_QUERY_PARSER_NAME,
			DS_QUERY_PARSER_VERSION,
			DS_QUERY_PARSER_AUTHOR
		);
	}

	public function Prepare($query) {
		$this->query = $query;
		$this->ExtractFields();
	}

	public function PrepareByResource($resource) {
		$this->Prepare($this->GetResourceByName($resource));
	}

	public function Bind(
		$field,
		$value,
		$delimiters = true,
		$escape     = true
	) {
		if(!$this->FindInArrayString($this->fields, $field))
			return false;
		if($escape)
			$value = $this->Escape($value);
		if($delimiters)
			$value = "'".$value."'";

		$this->keyValues[$field] = $value;
		
		return true;
	}

	public function BindNull($field, $value) {
		$empty = strlen($value) == 0;
		return $this->Bind($field, $empty ? "NULL" : $value, !$empty);
	}

	public function UnBind($field) {
		$found = false;
		$count = count($this->fields);
		for($i = 0; $i < $count; $i++) {
			if($this->fields[$i] == $field) {
				unset($this->fields[$i]);
				unset($this->keyValues[$field]);
				$found = true;
			}
		}

		return $found;
	}

	public function GetQuery() {
		return $this->query;
	}

	public function GetParsedQuery() {
		$count = count($this->fields);
		if($count == 0)
			return $this->query;

		$tmp      = $this->query;
		$tmpField = "";
		$pos      = 0;

		for($i = 0; $i < $count; $i++) {
			$tmpField = ":".$this->fields[$i].":";

			$pos = strpos($tmp, $tmpField, $pos);
			if($pos !== false) {
				$tmp = substr_replace(
					$tmp,
					$this->keyValues[$this->fields[$i]],
					$pos,
					strlen($tmpField)
				);

				$pos += strlen($this->keyValues[$this->fields[$i]]) + 1;
			}
		}

		return $tmp;
	}

	protected function ExtractFields() {
		$this->fields = array();
		$length       = strlen($this->query);

		if($length == 0)
			return 0;

		$in  = false;
		$tmp = "";
		$c   = "";
		$i   = 0;
		for(; $i < $length; $i++) {
			$c = $this->query[$i];
			
			if($c == ":" && $in) {
				$in                    = false;
				$this->fields[]        = $tmp;
				$this->keyValues[$tmp] = "";
				$tmp                   = "";
			} else if($c == ":" && !$in) {
				$in = true;
				continue;
			}

			if($in)
				$tmp .= $c;
		}

		return $i;
	}

	protected function RemoveFields() {
		$count = count($this->fields);
		$this->fields = array();
		return $count;
	}

	protected function FindInArrayString($array, $field) {
		foreach($array as $value) {
			if($value == $field)
				return true;
		}

		return false;
	}

	public function Escape($value) {
		$value = str_replace("\\", "\\\\", $value);
		$value = str_replace("'", "\\'", $value);
		return $value;
	}

	public function &EscapeReference(&$value) {
		$value = str_replace("\\", "\\\\", $value);
		$value = str_replace("'", "\\'", $value);
		return $value;
	}

}

?>
