<?php

require_once "DSDatabase.php";
require_once "DSClassInfo.php";

define("DS_POSTGRESQL_DATABASE_VERSION", "0.0.1");
define("DS_POSTGRESQL_DATABASE_NAME",    "DSPostgreSQLDatabase");
define("DS_POSTGRESQL_DATABASE_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSPostgreSQLDatabase extends DSDatabase {

	protected $connection = null;

	public function __construct(
		$hostname = "",
		$database = "",
		$username = "",
		$password = "",
		$port     = 5432
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
			DS_POSTGRESQL_DATABASE_NAME,
			DS_POSTGRESQL_DATABASE_VERSION,
			DS_POSTGRESQL_DATABASE_AUTHOR
		);
	}

	public function Connect() {
		$this->connection = pg_connect(sprintf(
			"host=%s dbname=%s user=%s password=%s port=%s",
			$this->GetHostname(),
			$this->GetDatabase(),
			$this->GetUsername(),
			$this->GetPassword(),
			$this->GetPort()
		));

		if(!$this->connection) {
			$this->connection = null;
			return false;
		}

		return true;
	}

	public function IsConnected() {
		return pg_connection_status($this->connection) == PGSQL_CONNECTION_OK;
	}

	public function Reconnect() {
		if(!$this->IsConnected())
			return $this->Connect();
		return true;
	}

	public function Disconnect() {
		if($this->IsConnected()) {
			pg_close($this->connection);
			return true;
		}

		return false;
	}

	public function GetConnection() {
		return $this->connection;
	}

}

?>
