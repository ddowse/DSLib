<?php

require_once "DSData.php";
require_once "DSClassInfo.php";

define("DS_SESSION_VERSION", "0.0.1");
define("DS_SESSION_NAME",    "DSSession");
define("DS_SESSION_AUTHOR",  "Thorsten Geppert (thorsten@ext2fs.de)");

class DSSession extends DSData {

	public function __construct(DSQuery $query) {
		parent::__construct($query);
	}

	public function GetClassInfo() {
		return new DSClassInfo(
			DS_SESSION_NAME,
			DS_SESSION_VERSION,
			DS_SESSION_AUTHOR
		);
	}

	public function CreateNewSession($information = "") {
		$sessionId = "";

		do {
			$sessionId = $this->CreateNewSessionId();
		} while($this->Exists($sessionId));

		$this->query->Prepare("
			INSERT INTO sessions (
				id, 
				ip, 
				useragent, 
				countdown, 
				information
			) VALUES (
				:id:, 
				:ip:, 
				:useragent:, 
				NOW(), 
				:information:
			)
		");
		$this->query->Bind("id", $sessionId);
		$this->query->Bind("ip", $_SERVER["REMOTE_ADDR"]);
		$this->query->Bind("useragent", $_SERVER["HTTP_USER_AGENT"]);
		$this->query->Bind("information", $information);
		$this->query->Exec(false);

		$this->DeleteOld();

		return $sessionId;
	}

	public function Exists($sessionId) {
		$this->query->Prepare("SELECT COUNT(*) AS counter FROM sessions WHERE id = :id:");
		$this->query->Bind("id", $sessionId);
		$this->query->Exec();
		$this->query->NextRecord();
		$exists = $this->query->GetField("counter") > 0;
		$this->query->FreeResult();
		return $exists;
	}

	public function IsValid($sessionId, $actualize = true) {
		$this->query->Prepare("
			SELECT 
				COUNT(id) AS counter 
			FROM 
				sessions 
			WHERE 
				id = :id: 
			AND 
				EXTRACT('epoch' FROM countdown) + 21600 >= EXTRACT('epoch' FROM NOW()) 
			AND 
				useragent = :useragent: 
			AND 
				ip = :ip:
		");
		$this->query->Bind("id", $sessionId);
		$this->query->Bind("ip", $_SERVER["REMOTE_ADDR"]);
		$this->query->Bind("useragent", $_SERVER["HTTP_USER_AGENT"]);
		$this->query->Exec();
		$this->query->NextRecord();
		$active = $this->query->GetField("counter") > 0;
		$this->query->FreeResult();

		if($actualize == true) {
			$this->query->Prepare("UPDATE sessions SET countdown = NOW() WHERE id = :id:");
			$this->query->Bind("id", $sessionId);
			$this->query->Exec(false);
		}

		$this->DeleteOld();

		return $active;
	}

	public function CreateNewSessionId() {
		return rand(11111111, 99999999);
	}

	protected function DeleteOld() {
		return $this->query->Query("
				DELETE FROM 
					sessions 
				WHERE 
					EXTRACT('epoch' FROM countdown) + 21600 < EXTRACT('epoch' FROM NOW())
			",
			false
		);
	}

	public function RemoveSession($sessionId) {
		$this->query->Prepare("DELETE FROM sessions WHERE id = :id:");
		$this->query->Bind("id", $sessionId);
		return $this->query->Exec(false);
	}

	public function GetInformation($sessionId) {
		$information = "";
		
		$this->query->Prepare("SELECT information FROM sessions WHERE id = :id:");
		$this->query->Bind("id", $sessionId);
		$this->query->Exec();
		if($this->query->NextRecord())
			$information = $this->query->GetField("information");
		$this->query->FreeResult();

		return $information;
	}

	public function SetInformation($sessionId, $information) {
		$this->query->Prepare("UPDATE sessions SET information = :information: WHERE id = :id:");
		$this->query->Bind("information", $information);
		$this->query->Bind("id", $sessionId, false);
		return $this->query->Exec(false);
	}

}

?>
