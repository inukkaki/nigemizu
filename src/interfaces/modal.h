#ifndef NIGEMIZU_INTERFACES_MODAL_H_
#define NIGEMIZU_INTERFACES_MODAL_H_

namespace nigemizu::interfaces::modal {

void ShowErrorMessage(const char* title, const char* message);
void ShowErrorMessage(
    const char* title, const char* message, const char* quotation);

}  // namespace nigemizu::interfaces::modal

#endif  // NIGEMIZU_INTERFACES_MODAL_H_
