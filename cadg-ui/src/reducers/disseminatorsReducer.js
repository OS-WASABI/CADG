/// Reduces actions dispatched for the cmsp store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * cmsp data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file alertsReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import {  /// Alert action types.
  GET_CMSPS,
  CREATE_CMSP,
  UPDATE_CMSP,
  REMOVE_CMSP } from "../actions/types";

const initialState = {  /// Initialized with no active alerts.
  active: {},
}

/// Main reducer for cmsp actions.
/**
 * Uses a switch statement to modify the cmsp store. Switch statement is used
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
    case GET_CMSPS:
      return {
        ...state
      };
    case CREATE_CMSP:
      return {
        ...state,
      }
    case UPDATE_CMSP:
      return {
        ...state,
      };
    case REMOVE_CMSP:
      return {
        ...state,
      };
    default:
      return state;
  }
}