#pragma once

#include <concepts>

#include "common_net.hpp"

namespace common_ns {

// class GenericLayerEntity {
// public:
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::UNDEF_IDX};

// protected:
// private:
// };

// class GenericL1Entity : public GenericLayerEntity {
// public:
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::PHYSICAL_IDX};

// protected:
// private:
// };

// class GenericL2Entity : public GenericLayerEntity {
// public:
//   using address_t = void *;
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::DATALINK_IDX};

//   virtual address_t const &getAddress() const = 0;

// protected:
// private:
// };

// class GenericL3Entity : public GenericLayerEntity {
// public:
//   using address_t = void *;
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::NETWORK_IDX};

//   virtual address_t const &getAddress() const = 0;

// protected:
// private:
// };

// /*
//  * Transport Layer :
//  */
// class GenericL4Entity : public GenericLayerEntity {
// public:
//   using address_t = void *;
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::TRANSPORT_IDX};

//   virtual address_t const &getAddress() const = 0;

// protected:
// private:
// };

// class GenericL5Entity : public GenericLayerEntity {
// public:
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::SESSION_IDX};

// protected:
// private:
// };

// class GenericL6Entity : public GenericLayerEntity {
// public:
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::PRESENTATION_IDX};

// protected:
// private:
// };

// class GenericL7Entity : public GenericLayerEntity {
// public:
//   static constexpr OsiLayer LAYER_IDX{OsiLayer::APPLICATION_IDX};

// protected:
// private:
// };

// // STATIC ASSERTIONS

// // STATIC ASSERTIONS - adressable entities

// // For now, I'm assuming all L1, L2, L3 and L4 entities are addressable,
// // although there may be exceptions in practice. When I encounter them,
// nmaybe
// // I'll apply these assertions to specific entities instead (e.g. IP, TCP,
// UDP,
// // etc.)

// static_assert(IsAddressableEntity<GenericL2Entity>,
//               "GenericL2Entity does not satisfy IsAddressableLayerType
//               concept " "requirements !");
// static_assert(IsAddressableEntity<GenericL3Entity>,
//               "GenericL3Entity does not satisfy IsAddressableLayerType
//               concept " "requirements !");
// static_assert(IsAddressableEntity<GenericL4Entity>,
//               "GenericL4Entity does not satisfy IsAddressableLayerType
//               concept " "requirements !");

// CONCEPTS

template <typename T>
concept IsL1EntityType =
    (T::LAYER_IDX == OsiLayer::PHYSICAL_IDX) && requires(const T &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    } && IsAddressableEntity<T>;

template <typename T>
concept IsL2EntityType =
    (T::LAYER_IDX == OsiLayer::DATALINK_IDX) && requires(const T &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    } && IsAddressableEntity<T>;

template <typename T>
concept IsL3EntityType =
    (T::LAYER_IDX == OsiLayer::NETWORK_IDX) && requires(const T &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    } && IsAddressableEntity<T>;

template <typename T>
concept IsL4EntityType =
    (T::LAYER_IDX == OsiLayer::TRANSPORT_IDX) && requires(T const &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    } && IsAddressableEntity<T>;

template <typename T>
concept IsL5EntityType =
    (T::LAYER_IDX == OsiLayer::SESSION_IDX) && requires(const T &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    };

template <typename T>
concept IsL6EntityType =
    (T::LAYER_IDX == OsiLayer::PRESENTATION_IDX) && requires(const T &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    };

template <typename T>
concept IsL7EntityType =
    (T::LAYER_IDX == OsiLayer::APPLICATION_IDX) && requires(const T &entity) {
      { T::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
    };

} // namespace common_ns