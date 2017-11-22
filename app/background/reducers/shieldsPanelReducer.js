/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as shieldsPanelTypes from '../../constants/shieldsPanelTypes'
import {setAllowAdBlock, setAllowTrackingProtection, toggleShieldsValue} from '../api/shieldsAPI'
import {setBadgeText} from '../api/badgeAPI'

export default function shieldsPanelReducer (state = {tabs: {}}, action) {
  switch (action.type) {
    case shieldsPanelTypes.SHIELDS_PANEL_DATA_UPDATED:
      state = {...state, ...action.details}
      break
    case shieldsPanelTypes.SHIELDS_TOGGLED:
      setAllowAdBlock(state.origin, toggleShieldsValue(state.adBlock))
        .catch(() => {
          console.error('Could not set ad block setting')
        })
      setAllowTrackingProtection(state.origin, toggleShieldsValue(state.trackingProtection))
        .catch(() => {
          console.error('Could not set tracking protection setting')
        })
      break
    case shieldsPanelTypes.AD_BLOCK_TOGGLED:
      setAllowAdBlock(state.origin, toggleShieldsValue(state.adBlock))
        .catch(() => {
          console.error('Could not set ad block setting')
        })
      break
    case shieldsPanelTypes.TRACKING_PROTECTION_TOGGLED:
      setAllowTrackingProtection(state.origin, toggleShieldsValue(state.trackingProtection))
        .catch(() => {
          console.error('Could not set tracking protection setting')
        })
      break
    case shieldsPanelTypes.RESOURCE_BLOCKED:
      const tabId = action.details.tabId
      const tabs = {...state.tabs}
      tabs[tabId] = state.tabs[tabId] || { adsBlocked: 0, trackingProtectionBlocked: 0 }
      if (action.details.blockType === 'adBlock') {
        tabs[tabId].adsBlocked++
      } else if (action.details.blockType === 'trackingProtection') {
        tabs[tabId].trackingProtectionBlocked++
      }
      state = {
        ...state,
        tabs
      }
      if (tabId === state.tabId) {
        setBadgeText(state.tabs[tabId].adsBlocked + state.tabs[tabId].trackingProtectionBlocked)
      }
      break
  }
  return state
}
