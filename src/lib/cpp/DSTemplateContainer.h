#ifndef DS_TEMPLATE_CONTAINER_H_
#define DS_TEMPLATE_CONTAINER_H_

#include <wx/wx.h>
#include <vector>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_TEMPLATE_CONTAINER_NAME		_N("DSContainerTemplate")
#define DS_TEMPLATE_CONTAINER_VERSION	_N("0.8.4")
#define DS_TEMPLATE_CONTAINER_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	template<class T>
	class DSTemplateContainer : public DSLib {

		protected:
			std::vector<T> data;
	
		public:
			DSTemplateContainer(
				const unsigned int init = 0
			) : DSLib(
			), data(
				init
			) {
			}

			DSClassInfo GetClassInfo() {
				return DynSoft::DSClassInfo(
					DS_TEMPLATE_CONTAINER_NAME,
					DS_TEMPLATE_CONTAINER_VERSION,
					DS_TEMPLATE_CONTAINER_AUTHOR
				);
			}

			T Add(T entry) {
				data.push_back(entry);
				return entry;
			}

			T Insert(T entry, unsigned int index) {
				if(index < GetCount() - 1) {
					data.insert(data.begin() + index, entry);
				} else {
					index -= (GetCount() - 1);
					if(index > 0)
						for(unsigned int i = 0; i < index - 1; i++)
							Add(NULL);
					Add(entry);
				}

				return entry;
			}

			T Get(unsigned int index) {
				if(index < GetCount())
					return data[index];
				return NULL;
			}

			unsigned int GetCount() const {
				return data.size();
			}

			unsigned int Remove(T entry, const bool removePointer) {
				T tmp;
				unsigned int found = 0;
				
				for(unsigned int i = 0; i < GetCount(); i++) {
					tmp = Get(i);
					if(tmp == entry) {
						data.erase(data.begin() + i);
						found++;
					}
				}

				if(removePointer) {
					delete entry;
					entry = NULL;
				}

				return found;
			}

			T Remove(const unsigned int index, const bool removePointer = false) {
				if(index < GetCount()) {
					T tmp = Get(index);
					data.erase(data.begin() + index);
					if(removePointer) {
						delete tmp;
						tmp = NULL;
					}
					return tmp;
				}
				
				return NULL;
			}

			int Find(T entry) {
				T tmp;
				for(unsigned int i = 0; i < GetCount(); i++) {
					tmp = Get(i);
					if(tmp == entry) {
						return (int) i;
					}
				}

				return -1;
			}

			void Clear(const bool removePointer = false) {
				while(this->GetCount() > 0)
					this->Remove((const unsigned int) 0, removePointer);
			}
	
	};

}

#endif /* DS_TEMPLATE_CONTAINER_H_ */
