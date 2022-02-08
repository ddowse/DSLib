<?php

require_once "DSQuery.php";
require_once "DSMySQLDatabase.php";
require_once "DSClassInfo.php";

define("DS_MYSQL_QUERY_VERSION", "0.0.1");
define("DS_MYSQL_QUERY_NAME",    "DSMySQLQuery");
define("DS_MYSQL_QUERY_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSMySQLQuery extends DSQuery {

	protected $connection = null;
	protected $running    = false;
	protected $result     = null;
	protected $row        = null;

	public function __construct(DSMySQLDatabase $db) {
		parent::__construct($db);
		
		$db->Reconnect();
		$this->connection = $db->GetConnection();
		$this->running    = false;
		
		$this->Prepare("SET NAMES :encoding:");
		$this->Bind("encoding", $db->GetEncoding(), false);
		$this->Exec(false);
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_MYSQL_QUERY_NAME,
			DS_MYSQL_QUERY_VERSION,
			DS_MYSQL_QUERY_AUTHOR
		);
	}

	public function Exec($storeResult = true) {
		$ok            = false;
		$this->running = false;
		$this->result = mysql_query($this->GetParsedQuery(), $this->connection);
		if($this->result) {
			if(!$storeResult) {
				$ok = true;
				$this->FreeResult();
			} else {
				$this->running = $this->result !== true;
				$ok            = $this->running;
			}
		}

		return $ok;
	}

	public function GetField($field) {
		return $this->row[$field];
	}

	public function IsNull($field) {
		return $this->GetField($field) == null;
	}

	public function GetColumn($column) {
		return mysql_field_name($this->result, $column);
	}

	public function GetRowCount() {
		if($this->running)
			return mysql_num_rows($this->result);
		return 0;
	}

	public function GetColumnCount() {
		return mysql_num_fields($this->result);
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
		$this->running = false;
		if($this->result !== false && $this->result !== true)
			mysql_free_result($this->result);
	}

	public function NextRecord() {
		if($this->running)
			if(($this->row = mysql_fetch_array($this->result)))
				return true;
		$this->running = false;
		return false;
	}

}

?>
