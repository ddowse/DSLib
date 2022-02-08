<?php

require_once "DSDatabase.php";
require_once "DSClassInfo.php";

define("DS_MYSQL_DATABASE_VERSION", "0.0.1");
define("DS_MYSQL_DATABASE_NAME",    "DSMySQLDatabase");
define("DS_MYSQL_DATABASE_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSMySQLDatabase extends DSDatabase {

	protected $connection = null;
	protected $flags      = 0;
	protected $encoding   = "utf8";

	public function __construct(
		$hostname = "",
		$database = "",
		$username = "",
		$password = "",
		$port     = 3306
	) {
		parent::__construct(
			$hostname,
			$database,
			$username,
			$password,
			$port
		);
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_MYSQL_DATABASE_NAME,
			DS_MYSQL_DATABASE_VERSION,
			DS_MYSQL_DATABASE_AUTHOR
		);
	}

	public function Connect($persistend = false) {
		if($persistend) {
			$this->connection = mysql_pconnect(
				$this->GetHostname().":".$this->GetPort(),
				$this->GetUsername(),
				$this->GetPassword(),
				false,
				$this->GetFlags()
			);
		} else {
			$this->connection = mysql_connect(
				$this->GetHostname().":".$this->GetPort(),
				$this->GetUsername(),
				$this->GetPassword(),
				false,
				$this->GetFlags()
			);
		}

		if(!$this->connection) {
			$this->connection = null;
			return false;
		}

		if(!mysql_select_db($this->database, $this->connection))
			return false;

		return true;
	}

	public function IsConnected() {
		return mysql_ping($this->GetConnection());
	}

	public function Reconnect() {
		return $this->IsConnected();
	}

	public function Disconnect() {
		return mysql_close($this->GetConnection());
	}

	public function SetFlags($flags) {
		$this->flags = $flags;
	}

	public function GetFlags() {
		return $this->flags;
	}

	public function SetEncoding($encoding) {
		$this->encoding = $encoding;
	}

	public function GetEncoding() {
		return $this->encoding;
	}

	public function GetConnection() {
		return $this->connection;
	}

}

?>
