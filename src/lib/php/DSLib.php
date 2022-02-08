<?php

require_once "DSClassInfo.php";
require_once "DSDatabase.php";

define("DS_LIB_VERSION",       "0.0.1");
define("DS_LIB_NAME",          "DSLib");
define("DS_LIB_AUTHOR",        "Thorsten Geppert (thorsten@ext2fs.de)");
define("DS_LIB_DESCRIBER_OR",  " ");
define("DS_LIB_DESCRIBER_AND", "+");
define("DS_LIB_DESCRIBER_NOT", "-");

abstract class DSLib {

	public static $OK         = 0;
	public static $ERROR_FILE = -1;

	protected $db             = null;
	protected $resource       = null;

	public function __construct(DSDatabase $db = null) {
		$this->db = $db;
	}

	public static function GetInfo() {
		return new DSClassInfo(
			DS_LIB_NAME,
			DS_LIB_VERSION,
			DS_LIB_AUTHOR
		);
	}

	public abstract function GetClassInfo();

	/*public function SetDatabase(DSDatabase $db) {
		$this->db = $db;
	}

	public function GetDatabase() {
		return $this->db;
	}*/

	public static function Split($string, $delimeter) {
		return explode($string, $delimeter);
	}

	public static function ParseSearchWord(
		$search,
		&$relations,
		&$words
	) {
		$counter = 0;
		if(
			$relations == null    ||
			$words     == null    ||
			!is_array($relations) ||
			!is_array($words)
		) {
			return $counter;
		}

		$tmp = "";
		$c = "";
		$describer = 0;

		for($i = 0; $i < strlen($search); $i++) {
			$c = $search[$i];

			if($c == "+" || $c == "-" || $c == " " || $i == 0) {
				if($i == 0 && $c != "+" && $c != "-") {
					$describer = DS_LIB_DESCRIBER_OR;
				} else {
					$describer = $c;
					continue;
				}
			}

			for(; $i < strlen($search); $i++) {
				$c = $search[$i];
				if($c == "+" || $c == "-" || $c == ' ') {
					$i--;
					break;
				} else if($c == "\"") {
					$i++;
					for(; $i < strlen($search); $i++) {
						$c = $search[$i];
						if($c == "\"" && $search[$i - 1] != "\\")
							break;
						$tmp .= $c;
					}
				} else {
					$tmp .= $c;
				}
			}

			switch($describer) {
				case DS_LIB_DESCRIBER_AND:
					$relations[] = "AND";
					break;
				case DS_LIB_DESCRIBER_NOT:
					$relations[] = "NOT";
					break;
				case DS_LIB_DESCRIBER_OR:
				default:
					$relations[] = "OR";
					break;
			}

			$words[] = $tmp;
			$tmp = "";

			$counter++;
		}

		return $counter;
	}

	public function PrintArrayString($messages) {
		$count = count($messages);
		for($i = 0; $i < $count; $i++)
			$this->PrintLine($messages[$i]);
	}

	public function PrintLine($message) {
		echo $message."\n";
	}

	public function LoadResourceFile($filename, &$resource) {
		$result = $OK;

		$lines = array();
		if($lines = @file($filename)) {
			$identifier = "";
			$line = "";
			$tmp = "";
			$count = count($lines);
			$stop = $count - 1;
			for($i = 0; $i < $count; $i++) {
				$line = $lines[$i];
				if($line != "") {
					if($line[0] != "\t" || $i == $stop)
						$tmp .= substr($line, 1)."\n";
					if($identifier != "") {
						$identifier = str_replace("\r", "", $identifier);
						$identifier = str_replace("\n", "", $identifier);
						$this->resource[$identifier] = $tmp;
						$tmp = "";
						$result++;
					}
					$identifier = $line;
				} else {
					$tmp .= substr($line, 1)."\n";
				}
			}
		} else {
			$result = $ERROR_FILE;
		}

		return $result;
	}

	public function LoadResource($filename) {
		return $this->LoadResourceFile($filename, $this->resource);
	}

	public function AppendResource($filename) {
		$this->ClearResource();
		return $this->LoadResourceFile($filename, $this->resource);
	}

	public function GetResourceByName($name) {
		return $this->resource[$name];
	}

	public function &GetResource() {
		return $this->resource;
	}

	public function res($name) {
		return $this->GetResourceByName($name);
	}

	public function ClearResource() {
		$size = count($this->resource);
		$this->resource = array();
		return $size;
	}

}

?>
