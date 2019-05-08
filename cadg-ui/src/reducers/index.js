/// The root reducer.
/**
 * The root reducer for the redux store. Combines all other reducers
 * from this directory into one root reducer.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    index.js
 * @date    February 2019
 * @authors Vaniya Agrawal
 */

import { combineReducers } from 'redux';
import { connectRouter } from 'connected-react-router'
import adminReducer from './adminsReducer';
import alertReducer from './alertsReducer';
import cmspReducer from './disseminatorsReducer';
import aogReducer from './aogsReducer';
import configuration from './configuration';

export default (history) => combineReducers({
  admins: adminReducer,
  alerts: alertReducer,
  cmsps: cmspReducer,
  aogs: aogReducer,
  config: configuration,
  router: connectRouter(history)
})