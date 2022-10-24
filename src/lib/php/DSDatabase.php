<?php

require_once "DSLib.php";
require_once "DSClassInfo.php";

define("DS_DATABASE_VERSION", "0.0.1");
define("DS_DATABASE_NAME",    "DSTemplate");
define("DS_DATABASE_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

abstract class DSDatabase extends DSLib {

	abstract public function Connect();
	abstract public function IsConnected();
	abstract public function Reconnect();
	abstract public function Disconnect();

	protected $hostname = "";
	protected $database = "";
	protected $username = "";
	protected $password = "";
	protected $port     = "";

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_DATABASE_NAME,
			DS_DATABASE_VERSION,
			DS_DATABASE_AUTHOR
		);
	}

	public function __construct(
		$hostname,
		$database,
		$username,
		$password,
		$port
	) {
		parent::__construct();

		$this->SetHostname($hostname);
		$this->SetDatabase($database);
		$this->SetUsername($username);
		$this->SetPassword($password);
		$this->SetPort($port);
	}

	public function SetHostname($hostname) {
		$this->hostname = $hostname;
	}

	public function GetHostname() {
		return $this->hostname;
	}

	public function SetDatabase($database) {
		$this->database = $database;
	}

	public function GetDatabase() {
		return $this->database;
	}

	public function SetUsername($username) {
		$this->username = $username;
	}

	public function GetUsername() {
		return $this->username;
	}

	public function SetPassword($password) {
		$this->password = $password;
	}

	public function GetPassword() {
		return $this->password;
	}

	public function SetPort($port) {
		$this->port = $port;
	}

	public function GetPort() {
		return $this->port;
	}

}

?>
