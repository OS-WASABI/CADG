/// Reduces actions dispatched for the alert store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * alert data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file alertsReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import {  /// Alert action types.
  GET_ALERTS,
  SEND_ALERT,
  UPDATE_ALERT,
  CANCEL_ALERT } from "../actions/types";

const initialState = {  /// Initialized with no active alerts.
  activeAlerts: {},
}

/// Home reducer for alert actions.
/**
 * Uses a switch statement to modify the alert store. Switch statement is used
 * to determine which action has been dispatched and to modify the store accordingly.
 *
 * IMPORTANT!! The store is IMMUTABLE. ALL cases must return a COPY of the store,
 * they must not change the store itself. Utilize a return statement and the spread
 * operator (ex.: ...state) to accomplish this.
 *
 * @param state The current state of the data.
 * @param action  The action that is dispatched. Contains a type and a payload.
 * @returns object  A copy of the store, modified according to the action type and payload.
 */
export default (state = initialState, action) => {
  switch(action.type) {
    case GET_ALERTS:
      return {
        ...state
      };
    case SEND_ALERT:
      return {
        ...state,
      }
    case UPDATE_ALERT:
      return {
        ...state,
      };
    case CANCEL_ALERT:
      return {
        ...state,
      };
    default:
      return state;
  }
}