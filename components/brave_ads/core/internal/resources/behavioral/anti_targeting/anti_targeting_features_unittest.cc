/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/resources/behavioral/anti_targeting/anti_targeting_features.h"

#include <vector>

#include "base/test/scoped_feature_list.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace brave_ads::resource::features {

TEST(BatAdsAntiTargetingFeaturesTest, IsAntiTargetingEnabled) {
  // Arrange

  // Act

  // Assert
  EXPECT_TRUE(IsAntiTargetingEnabled());
}

TEST(BatAdsUserActivityFeaturesTest, IsAntiTargetingDisabled) {
  // Arrange
  const std::vector<base::test::FeatureRefAndParams> enabled_features;

  std::vector<base::test::FeatureRef> disabled_features;
  disabled_features.emplace_back(kAntiTargeting);

  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitWithFeaturesAndParameters(enabled_features,
                                                    disabled_features);

  // Act

  // Assert
  EXPECT_FALSE(IsAntiTargetingEnabled());
}

TEST(BatAdsAntiTargetingFeaturesTest, GetAntiTargetingResourceVersion) {
  // Arrange
  base::FieldTrialParams params;
  params["resource_version"] = "0";
  std::vector<base::test::FeatureRefAndParams> enabled_features;
  enabled_features.emplace_back(kAntiTargeting, params);

  const std::vector<base::test::FeatureRef> disabled_features;

  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitWithFeaturesAndParameters(enabled_features,
                                                    disabled_features);

  // Act

  // Assert
  EXPECT_EQ(0, GetAntiTargetingResourceVersion());
}

TEST(BatAdsAntiTargetingFeaturesTest, DefaultAntiTargetingResourceVersion) {
  // Arrange

  // Act

  // Assert
  EXPECT_EQ(1, GetAntiTargetingResourceVersion());
}

TEST(BatAdsIdleDetectionFeaturesTest,
     DefaultAntiTargetingResourceVersionWhenDisabled) {
  // Arrange
  const std::vector<base::test::FeatureRefAndParams> enabled_features;

  std::vector<base::test::FeatureRef> disabled_features;
  disabled_features.emplace_back(kAntiTargeting);

  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitWithFeaturesAndParameters(enabled_features,
                                                    disabled_features);

  // Act

  // Assert
  EXPECT_EQ(1, GetAntiTargetingResourceVersion());
}

}  // namespace brave_ads::resource::features
