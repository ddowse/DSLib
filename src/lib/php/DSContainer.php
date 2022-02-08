<?php

require_once "DSLib.php";
require_once "DSClassInfo.php";
require_once "DSContainerType.php";

define("DS_CONTAINER_VERSION", "0.0.1");
define("DS_CONTAINER_NAME",    "DSContainer");
define("DS_CONTAINER_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSContainer extends DSLib {

	protected $data = array();

	public function __construct() {
		parent::__construct();
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_CONTAINER_NAME,
			DS_CONTAINER_VERSION,
			DS_CONTAINER_AUTHOR
		);
	}

	public function GetCount() {
		return count($this->data);
	}

	public function Add(DSContainerType $entry, $check = false) {
		$tmp = null;
		if($check) {
			$tmp   = $entry;
			$tmp2  = null;
			$count = $this->GetCount();
			for($i = 0; $i < $count; $i++) {
				$tmp2 = $this->Get($i);
				if($tmp2 != null) {
					if($tmp2->GetComparision() == $entry->GetComparision()) {
						$tmp = $tmp2;
						break;
					}
				}
			}
		}

		if($tmp != $entry)
			$this->data[] = $entry;

		return $tmp;
	}

	public function Get($index) {
		if($index < $this->GetCount())
			return $this->data[$index];
		return null;
	}

	public function Remove($index) {
		$entry = null;

		if($index < $this->GetCount()) {
			$entry = $this->Get($index);
			unset($this->data[$index]);
		}

		return $entry;
	}

?>
