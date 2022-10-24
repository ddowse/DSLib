<?php

require_once "DSType.php";
require_once "DSClassInfo.php";

define("DS_CONTAINER_TYPE_VERSION", "0.0.1");
define("DS_CONTAINER_TYPE_NAME",    "DSContainerType");
define("DS_CONTAINER_TYPE_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSContainerType extends DSType {

	protected $comparision = null;

	public function __construct($comparision = null) {
		parent::__construct();
		$this->comparision = $comparision;
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_CONTAINER_TYPE_NAME,
			DS_CONTAINER_TYPE_VERSION,
			DS_CONTAINER_TYPE_AUTHOR
		);
	}

	public function SetComparison($comparision) {
		$this->comparision = $comparision;
	}

	public function GetComparision() {
		return $this->comparision;
	}

?>
