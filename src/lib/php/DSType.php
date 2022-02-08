<?php

require_once "DSLib.php";
require_once "DSClassInfo.php";

define("DS_TYPE_VERSION", "0.0.1");
define("DS_TYPE_NAME",    "DSType");
define("DS_TYPE_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSType extends DSLib {

	public function __construct() {
		parent::__construct();
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_TYPE_NAME,
			DS_TYPE_VERSION,
			DS_TYPE_AUTHOR
		);
	}

}

?>
