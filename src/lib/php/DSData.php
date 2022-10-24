<?php

require_once "DSQuery.php";
require_once "DSClassInfo.php";

define("DS_DATA_VERSION", "0.0.1");
define("DS_DATA_NAME",    "DSData");
define("DS_DATA_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSData extends DSLib {

	protected $query = null;
	protected $running = false;

	public function __construct(DSQuery $query) {
		parent::__construct();
		$this->query = $query;
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_DATA_NAME,
			DS_DATA_VERSION,
			DS_DATA_AUTHOR
		);
	}

	public function GetRunning() {
		return $this->running;
	}

	public function SetQuery(DSQuery $query) {
		$oldQuery = $this->query;
		$this->query = $query;
		return $oldQuery;
	}

	public function GetQuery() {
		return $this->query;
	}

	public function Reset() {
		if($this->GetRunning())
			if($this->query != null)
				$this->query->FreeResult();
		$this->running = false;
	}

	public function Run() {
		if($this->query != null) {
			if($this->GetRunning()) {
				if($this->query->NextRecord()) {
					return true;
				} else {
					$this->Reset();
				}
			}
		}
		return false;
	}

	public function GetCount() {
		if($this->query != nul && $this->GetRunning())
			return $this->query->GetRowCount();
		else
			return 0;
	}

	public function Create($parsedQuery) {
		$this->running = $this->query->Query($parsedQuery);
		return $this->running;
	}
}

?>
