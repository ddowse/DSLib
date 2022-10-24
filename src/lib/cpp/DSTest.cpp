#include "DSTest.h"

DynSoft::DSTest::DSTestEntity::DSTestEntity(
) : DSType(
) {
	wxDateTime dt = wxDateTime::Now();
	SetTimeStamp((DSDateTime &) dt);
}

DynSoft::DSTest::DSTestEntity::DSTestEntity(
	const bool success,
	const wxString &description,
	const wxString &successMessage,
	const wxString &errorMessage,
	const DSDateTime &timeStamp
) : DSType(
) {
	SetSuccess(success);
	SetDescription(description);
	SetSuccessMessage(successMessage);
	SetErrorMessage(errorMessage);
	SetTimeStamp(timeStamp);
}

DynSoft::DSClassInfo DynSoft::DSTest::DSTestEntity::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TESTENTITY_NAME,
		DS_TESTENTITY_VERSION,
		DS_TESTENTITY_AUTHOR
	);
}

void DynSoft::DSTest::DSTestEntity::SetSuccess(const bool success) {
	this->success = success;
}

bool DynSoft::DSTest::DSTestEntity::GetSuccess() const {
	return success;
}

void DynSoft::DSTest::DSTestEntity::SetDescription(const wxString &description) {
	this->description = description;
}

wxString DynSoft::DSTest::DSTestEntity::GetDescription() const {
	return description;
}

void DynSoft::DSTest::DSTestEntity::SetSuccessMessage(const wxString &successMessage) {
	this->successMessage = successMessage;
}

wxString DynSoft::DSTest::DSTestEntity::GetSuccessMessage() const {
	return successMessage;
}

void DynSoft::DSTest::DSTestEntity::SetErrorMessage(const wxString &errorMessage) {
	this->errorMessage = errorMessage;
}

wxString DynSoft::DSTest::DSTestEntity::GetErrorMessage() const {
	return errorMessage;
}

void DynSoft::DSTest::DSTestEntity::SetTimeStamp(const DynSoft::DSDateTime &timeStamp) {
	this->timeStamp = timeStamp;
}

DynSoft::DSDateTime DynSoft::DSTest::DSTestEntity::GetTimeStamp() const {
	return timeStamp;
}


DynSoft::DSTest::DSTest(const wxString &module) : DSType() {
	this->module = module;
}

DynSoft::DSTest::~DSTest() {
	__GetEntities()->Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSTest::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TEST_NAME,
		DS_TEST_VERSION,
		DS_TEST_AUTHOR
	);
}

void DynSoft::DSTest::__Assert(
	const bool success,
	const wxString &description,
	const wxString &errorMessage,
	const wxString &successMessage
) {
	wxDateTime dt = wxDateTime::Now();
	DynSoft::DSTest::DSTestEntity *entity = new DynSoft::DSTest::DSTestEntity(
		success,
		description,
		successMessage,
		errorMessage,
		DynSoft::DSDateTime((DSDateTime &) dt)
	);
	entities.Add(entity);
}

DynSoft::DSTemplateContainer<DynSoft::DSTest::DSTestEntity *> *DynSoft::DSTest::__GetEntities() {
	return &entities;
}

wxString DynSoft::DSTest::__GetModule() const {
	return module;
}
