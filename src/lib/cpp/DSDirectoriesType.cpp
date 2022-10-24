#include "DSDirectoriesType.h"

DynSoft::DSDirectoriesType::DSDirectoriesType(const bool autoClean) : DSType() {
	SetAutoClean(autoClean);
}

DynSoft::DSDirectoriesType::~DSDirectoriesType() {
	directories.Clear(GetAutoClean());
	files.Clear(GetAutoClean());
}

DynSoft::DSClassInfo DynSoft::DSDirectoriesType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DIRECTORY_TYPE_NAME,
		DS_DIRECTORY_TYPE_VERSION,
		DS_DIRECTORY_TYPE_AUTHOR
	);
}

void DynSoft::DSDirectoriesType::SetAutoClean(const bool autoClean) {
	this->autoClean = autoClean;
}

bool DynSoft::DSDirectoriesType::GetAutoClean() const {
	return autoClean;
}

void DynSoft::DSDirectoriesType::AddDirectory(DynSoft::DSDirectoryType *directory) {
	directories.Add(directory);
}

unsigned int DynSoft::DSDirectoriesType::GetDirectoryCount() const {
	return directories.GetCount();
}

DynSoft::DSDirectoryType *DynSoft::DSDirectoriesType::GetDirectory(const unsigned int index) {
	return directories.Get(index);
}

void DynSoft::DSDirectoriesType::AddFile(DynSoft::DSFileType *file) {
	files.Add(file);
}

unsigned int DynSoft::DSDirectoriesType::GetFileCount() const {
	return files.GetCount();
}

DynSoft::DSFileType *DynSoft::DSDirectoriesType::GetFile(const unsigned int index) {
	return files.Get(index);
}
