/// Stores configuration settings for app.
/**
 * @file configuration.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */

const initialState = {  /// Initialized with no active alerts.
  server: 'https://wasabi.group/v1/cadg/api',
}


export default (state = initialState, action) => {
  switch(action.type) {
    default:
      return state;
  }
}