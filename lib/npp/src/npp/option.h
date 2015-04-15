#pragma once

#include <functional>

namespace npp {

  /// A Option type, like in rust
  template<typename TValue>
  class Option {
    private:

      /// Currently ok?
      bool valid;

      /// Current value
      TValue value;

    public:

      /// New ok value
      static Option<TValue> Some(TValue value) {
        Option<TValue> rtn;
        rtn.value = value;
        rtn.valid = true;
        return rtn;
      }

      /// New err value
      static Option<TValue>None() {
        Option<TValue> rtn;
        rtn.valid = false;
        return rtn;
      }

      /// Overload bool cast
      operator bool() {
        return this->valid;
      }

      /// Overload * to get value
      TValue operator*() {
        return this->value;
      }

      /// Perform some action on success or error
      bool Then(std::function< void(TValue t)> on_some) {
        if (this->valid) {
          on_some(this->value);
          return true;
        }
        return false;
      }

      /// Get the value or the default value provided
      TValue Or(TValue default_value) {
        return this->valid ? this->value : default_value;
      }
  };

  /// Shortcut to create an Ok value
  template<typename TValue> Option<TValue> Some(TValue ok) {
    return Option<TValue>::Some(ok);
  }

  /// Shortcut to create an Err value
  template<typename TValue> Option<TValue> None() {
    return Option<TValue>::None();
  }
}
