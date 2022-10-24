<?php

define("DS_CLASS_INFO_NAME",    "DSClassInfo");
define("DS_CLASS_INFO_VERSION", "0.0.1");
define("DS_CLASS_INFO_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSClassInfo {

	protected $name    = "";
	protected $version = "";
	protected $author  = "";

	public function __construct(
		$name,
		$version,
		$author
	) {
		$this->SetName($name);
		$this->SetVersion($version);
		$this->SetAuthor($author);
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_CLASS_INFO_NAME,
			DS_CLASS_INFO_VERSION,
			DS_CLASS_INFO_AUTHOR
		);
	}

	public function SetName($name) {
		$this->name = $name;
	}

	public function GetName() {
		return $this->name;
	}

	public function SetVersion($version) {
		$this->version = $version;
	}

	public function GetVersion() {
		return $this->version;
	}

	public function SetAuthor() {
		$this->author = $author;
	}

	public function GetAutor() {
		return $this->author;
	}

}

?>
