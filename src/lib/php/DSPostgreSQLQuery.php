<?php

require_once "DSQuery.php";
require_once "DSPostgreSQLDatabase.php";
require_once "DSClassInfo.php";

define("DS_POSTGRESQL_QUERY_VERSION", "0.0.1");
define("DS_POSTGRESQL_QUERY_NAME",    "DSPostgreSQLQuery");
define("DS_POSTGRESQL_QUERY_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSPostgreSQLQuery extends DSQuery {

	protected $connection = null;
	protected $row        = 0;
	protected $result     = null;
	protected $running    = false;
	protected $record     = null;

	public function __construct(DSPostgreSQLDatabase $db) {
		parent::__construct($db);
		$this->connection = $db->GetConnection();
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_POSTGRESQL_QUERY_NAME,
			DS_POSTGRESQL_QUERY_VERSION,
			DS_POSTGRESQL_QUERY_AUTHOR
		);
	}

	public function Exec($storeResult = true) {
		$this->db->Reconnect();

		$this->row     = 0;
		$this->running = false;

		$this->result = pg_query($this->connection, $this->GetParsedQuery());
		if(!$this->result) {
			return false;
		} else {
			if(!$storeResult)
				$this->FreeResult();
			else
				$this->running = true;
		}

		return true;
	}

	public function GetField($field) {
		if($this->record)
			return $this->record[$field];
		return null;
	}

	public function NextRecord() {
		if($this->result) {
			$this->record = pg_fetch_array($this->result);
			$this->row++;
			return is_array($this->record);
		}

		return false;
	}

	public function IsNull($field) {
		return pg_field_is_null($this->result, $this->row, $field);
	}

	public function GetRowCount() {
		if($this->result)
			return pg_num_rows($this->result);
		return 0;
	}


	public function GetColumnCount() {
		if($this->result)
			return pg_num_fields($this->result);
		return 0;
	}

	public function Begin() {
		return $this->Query("BEGIN", false);
	}

	public function Commit() {
		return $this->Query("COMMIT", false);
	}

	public function Rollback() {
		return $this->Query("ROLLBACK", false);
	}

	public function FreeResult() {
		pg_free_result($this->result);
	}

}

?>
