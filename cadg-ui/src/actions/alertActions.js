/// Defines actions the involve alert data.
/**
 * Defines the actions that can occur to manage alert data.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alertActions.js
 * @date    February 2019
 * @authors Vaniya Agrawal
 */
import {
  GET_ALERTS,
  SEND_ALERT,
  UPDATE_ALERT,
  CANCEL_ALERT } from "./types";

/// Get alert data.
/**
 * Gets alert data from the server. If all alert data is being requested,
 * the query must be null. Otherwise, the query must include the key
 * and value to search on. For instance:
 *    { alertID: 0 },
 *    { severity: 'URGENT' }
 * @param query The search parameter in the form {key: value}
 * @returns {Function}  Dispatches an action.
 */
export const getAlerts = (query) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts')
    .then(res => res.json())
    .then(alerts => dispatch({
      type: GET_ALERTS,
      payload: alerts
    }));
};

/// Post alert data.
/**
 * Posts alert data to the server. The alert data is contained in the body
 * of the request and contains all necessary information.
 * @param alert Contains all necessary items defined by the CAP standard.
 * @returns {Function}  Dispatches an action.
 */
export const sendAlert = (alert) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(alert)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: SEND_ALERT,
      payload: res
    }));
};

/// Post updated alert data.
/**
 * Posts new alert data to the server.
 * @param alert Contains all necessary items defined for an update by the CAP standard.
 * @returns {Function}  Dispatches an action.
 */
export const updateAlert = (alert) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(userData)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: UPDATE_ALERT,
      payload: res
    }))
};

/// Post alert cancellation data.
/**
 * Posts alert cancellation data to the server.
 * @param alert Contains all necessary items defined by the CAP standard for a cancelling alert.
 * @returns {Function}  Dispatches an action.
 */
export const cancelAlert = (alert) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(alert)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: CANCEL_ALERT,
      payload: res
    }))
};