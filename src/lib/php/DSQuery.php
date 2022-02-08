<?php

require_once "DSDatabase.php";
require_once "DSQueryParser.php";
require_once "DSClassInfo.php";

define("DS_QUERY_VERSION", "0.0.1");
define("DS_QUERY_NAME",    "DSQuery");
define("DS_QUERY_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

abstract class DSQuery extends DSQueryParser {

	protected $db          = null;
	protected $storeResult = false;
	protected $running     = false;

	public function __construct(DSDatabase $db) {
		parent::__construct();

		$this->db          = $db;
		$this->storeResult = false;
		$this->running     = false;
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_QUERY_NAME,
			DS_QUERY_VERSION,
			DS_QUERY_AUTHOR
		);
	}

	abstract public function Exec($storeResult = true);
	abstract public function GetField($field);
	abstract public function IsNull($field);
	abstract public function GetRowCount();
	abstract public function GetColumnCount();
	abstract public function Begin();
	abstract public function Commit();
	abstract public function Rollback();
	abstract public function NextRecord();
	abstract public function FreeResult();

	public function Query(
		$query,
		$storeResult = true
	) {
		$this->query = $query;
		return $this->Exec($storeResult);
	}

	public function QueryByResource(
		$resource,
		$storeResult
	) {
		return $this->Query($this->GetResourceByName($resource), $storeResult);
	}

	public function IsRunning() {
		return $this->running;
	}

	public function GetDb() {
		return $db;
	}

}

?>
