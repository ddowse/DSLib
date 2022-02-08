<?php

require_once "DSLib.php";
require_once "DSClassInfo.php";
require_once "DSConstants.php";

define("DS_TEMPLATE_VERSION", "0.0.1");
define("DS_TEMPLATE_NAME",    "DSTemplate");
define("DS_TEMPLATE_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSTemplate extends DSLib {

	protected $root          = "";
	protected $content       = "";
	protected $parsedContent = "";
	protected $filename      = "";
	protected $intern        = array();
	protected $dynamic       = array();
	protected $variables     = array();

	public function __construct($root = "") {
		parent::__construct();

		$this->root = $root;
		if(strlen($this->root) > 0)
			if($this->root[strlen($this->root) - 1] != DS_PATH_SEPARATOR)
				$this->root .= "/";
		$this->FillInternVariables();
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_TEMPLATE_NAME,
			DS_TEMPLATE_VERSION,
			DS_TEMPLATE_AUTHOR
		);
	}

	protected function FillInternVariables() {
		$this->SetInternVariable("date", date("Y-m-d"));
		$this->SetInternVariable("time", date("h:i:s"));
		$this->SetInternVariable("datetime", date("Y-m-d"));
	}

	public function GetRoot() {
		return $this->root;
	}

	public function SetContent($content) {
		$this->content = $content;
	}

	public function SetFile($filename) {
		$this->filename = $filename;
		if($this->content = @file_get_contents($this->root.$filename))
			return DS_FILE_NOT_READ;
		return DS_OK;
	}

	public function &GetContent() {
		return $this->content;
	}

	public function GetContentCopy() {
		return $this->content;
	}

	public function &Get() {
		return $this->parsedContent;
	}

	public function GetCopy() {
		return $this->parsedContent;
	}

	public function SetVariable(
		$key,
		$value,
		$htmlSpecialChars = false
	) {
		$this->variables[$key] = $htmlSpecialChars ? htmlspecialchars($value) : $value;	
	}

	public function GetVariable($key) {
		return $this->variables[$key];
	}

	public function SetInternVariable(
		$key,
		$value,
		$htmlSpecialChars = false
	) {
		$this->intern[$key] = $htmlSpecialChars ? htmlspecialchars($value) : $value;
	}

	public function GetInternVariable($key) {
		return $this->intern[$key];
	}

	public function GetInternVariables() {
		return $this->intern;
	}

	public function SetDynamicVariable(
		$key,
		$value,
		$htmlSpecialChars = false
	) {
		$this->dynamic[$key] = $htmlSpecialChars ? htmlspecialchars($value) : $value;
	}

	public function GetDynamicVariable($key) {
		return $this->dynamic[$key];
	}

	public function Parse() {
		$tmp = $this->content;

		foreach($this->variables as $key => $value)
			$tmp = str_replace("{s:".$key."}", $value, $tmp);
		foreach($this->intern as $key => $value)
			$tmp = str_replace("{i:".$key."}", $value, $tmp);
		foreach($this->dynamic as $key => $value)
			$tmp = str_replace("{d:".$key."}", $value, $tmp);

		$this->parsedContent .= $tmp;

		return $tmp;
	}

	public function Show() {
		echo $this->parsedContent;
	}

	public function ClearParsed() {
		$this->parsedContent = array();
	}

}

?>
