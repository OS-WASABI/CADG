/// Reduces actions dispatched for the aog store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * aog data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file alertsReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import {  /// Alert action types.
  GET_AOGS,
  CREATE_AOG,
  UPDATE_AOG,
  REMOVE_AOG } from "../actions/types";

const initialState = {  /// Initialized with no active alerts.
  aogs: {
    0: {
      originator_id: 0,
      originator_name: 'FDNY',
      status: 'ACTIVE',
      agency: 'New York City'
    },
  }
}

/// Main reducer for aog actions.
/**
 * Uses a switch statement to modify the aog store. Switch statement is used
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
    case GET_AOGS:
      return {
        ...state
      };
    case CREATE_AOG:
      return {
        ...state,
      }
    case UPDATE_AOG:
      return {
        ...state,
      };
    case REMOVE_AOG:
      return {
        ...state,
      };
    default:
      return state;
  }
}