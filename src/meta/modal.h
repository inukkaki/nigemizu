#ifndef NIGEMIZU_META_MODAL_H_
#define NIGEMIZU_META_MODAL_H_

namespace nigemizu::meta::modal {

void ShowErrorMessage(const char* title, const char* message);
void ShowErrorMessage(
    const char* title, const char* message, const char* quotation);

}  // namespace nigemizu::meta::modal

#endif  // NIGEMIZU_META_MODAL_H_
