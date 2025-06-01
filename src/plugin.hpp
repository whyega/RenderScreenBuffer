#pragma once

#include <plugintmplt/plugintmplt.hpp>

class Plugin final : public plugintmplt::AbstractPlugin<Plugin> {
 private:
 public:
  void OnAttach(void* handle) override;
  void OnDetach() override;
};