/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_AI_CHAT_ANDROID_AI_CHAT_CM_HELPER_ANDROID_H_
#define BRAVE_BROWSER_AI_CHAT_ANDROID_AI_CHAT_CM_HELPER_ANDROID_H_

#include <memory>

#include "base/android/jni_android.h"
#include "base/android/scoped_java_ref.h"
#include "base/memory/raw_ptr.h"
#include "brave/components/ai_chat/core/browser/ai_chat_credential_manager.h"
#include "brave/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "mojo/public/cpp/bindings/receiver_set.h"

namespace ai_chat {

class AIChatCMHelperAndroid : public mojom::CredentialManagerHelper {
 public:
  AIChatCMHelperAndroid(
      const base::android::JavaParamRef<jobject>& jbrowser_context_handle);
  ~AIChatCMHelperAndroid() override;

  void Destroy(JNIEnv* env);

  void GetPremiumStatus(GetPremiumStatusCallback callback) override;
  jlong GetInterfaceToCredentialManagerHelper(JNIEnv* env);

 private:
  void OnPremiumStatusReceived(
      mojom::PageHandler::GetPremiumStatusCallback parent_callback,
      mojom::PremiumStatus premium_status,
      mojom::PremiumInfoPtr premium_info);
  std::unique_ptr<AIChatCredentialManager> credential_manager_;
  mojo::ReceiverSet<mojom::CredentialManagerHelper> receivers_;
  base::WeakPtrFactory<AIChatCMHelperAndroid> weak_ptr_factory_{this};
};

}  // namespace ai_chat

#endif  // BRAVE_BROWSER_AI_CHAT_ANDROID_AI_CHAT_CM_HELPER_ANDROID_H_
