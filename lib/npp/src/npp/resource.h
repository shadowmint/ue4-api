#include "option.h"
#include "iterator.h"
#include "types.h"

using namespace std;

namespace npp {

  /// An intrusive linked list for collecting resource instances
  template<typename TId, typename TValue>
  class Resource {
    private:

      /// Next item in the chain
      unique_ptr<Resource<TId, TValue>> data;

    protected:

      /// The id this value
      TId id;

      /// The value on this value
      TValue value;

    public:

      /// Create a new instance and assign the values to it
      Resource(TId id, TValue value) {
        this->id = id;
        this->value = value;
      }

      /// Destructor
      virtual ~Resource() {
      }

      /// Safely clone a new instance of this
      virtual Resource<TId, TValue> *Clone() = 0;

      /// Overload * to get value
      TValue operator*() {
        TValue rtn = this->value;
        return rtn;
      }

      /// Check if the id matches
      bool Is(TId id) {
        return this->id == id;
      }

      /// Return the next item in the chain
      Option<Resource<TId, TValue>*> Next() {
        if (data) {
          return Some<Resource<TId, TValue>*>(data.get());
        }
        return None<Resource<TId, TValue>*>();
      }

      /// Find the final link in this chain of values
      Resource<TId, TValue> *Last() {
        Resource<TId, TValue> *rtn = this;
        while (rtn->Next()) {
          rtn = *rtn->Next();
        }
        return rtn;
      }

      /// Push a resource onto the chain
      void Push(Resource<TId, TValue>* value) {
        if (data) {
          auto last = Last();
          last->Push(value);
        }
        else {
          data = unique_ptr<Resource<TId, TValue>>(value);
        }
      }

      /// Return resource chain length
      i32 Count() {
        return Iter<void>().Count();
      }

      /// Return an iterator to the contents
      template<typename TOut>
      Iterator<Resource<TId, TValue>*, TOut*> Iter() {
        return iter<Resource<TId, TValue>, TOut*>(this, [] (Resource<TId, TValue>* root, std::function< bool(TOut *value) > handler) {
          auto tmp = root;
          while(tmp) {
            if (!handler((TOut *) tmp))
              break;
            tmp = tmp->Next().Or(NULL);
          }
        });
      }

      /// Return an iterator to the contents, by id value
      template<typename TOut>
      Iterator<Resource<TId, TValue>*, TOut*> Iter(TId query) {
        return iter<Resource<TId, TValue>, TOut*>(this, [query] (Resource<TId, TValue>* root, std::function< bool(TOut *value) > handler) {
          auto tmp = root;
          while(tmp) {
            if (tmp->Is(query)) {
              if (!handler((TOut *) tmp))
                break;
            }
            tmp = tmp->Next().Or(NULL);
          }
        });
      }

      /// Return an iterator to the contents, by custom filter
      /// ...oddly, this is actually useful.
      template<typename TOut>
      Iterator<Resource<TId, TValue>*, TOut*> Iter(std::function< bool(Resource<TId, TValue>*) > filter) {
        return iter<Resource<TId, TValue>, TOut*>(this, [filter] (Resource<TId, TValue>* root, std::function< bool(TOut *value) > handler) {
          auto tmp = root;
          while(tmp) {
            if (filter(tmp)) {
              if (!handler((TOut *) tmp))
                break;
            }
            tmp = tmp->Next().Or(NULL);
          }
        });
      }


      /// Create a new resource chain with a custom filter
      Option<Resource<TId, TValue>*> Filter(std::function< bool(Resource<TId, TValue>*) > filter) {
        auto iter = this->Iter<Resource<TId, TValue>>(filter);
        if (iter.Any()) {
          auto index = 0;
          auto root = (*iter.First())->Clone();
          iter.Each([&] (Resource<TId, TValue>* r) {
            if (index != 0) {
              root->Push(r->Clone());
            }
            ++index;
          });
          return Some<Resource<TId, TValue>*>(root);
        }
        return None<Resource<TId, TValue>*>();
      }
  };
}
