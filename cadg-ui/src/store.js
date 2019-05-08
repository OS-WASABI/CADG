// A centralized store for shared state.
/**
 * This class creates a centralized store for shared state in the
 * GUI. It also applies middleware to the store so async fetches can be
 * made (with Thunk) and Redux DevTools (a Google Chrome extension) can
 * be utilized for testing purposes.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file store.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import { createStore, applyMiddleware, compose } from 'redux';
import thunk from 'redux-thunk';
import { routerMiddleware } from 'connected-react-router';
import createHistory from 'history/createBrowserHistory';
import rootReducer from './reducers';

export const history = createHistory();
const initialState = {};  // Represents the root of the store
const enhancers = [];
const middleware = [
  thunk,
  routerMiddleware(history)
]; // Specifies which middleware is being utilized

if (process.env.NODE_ENV === 'development') {
  const devToolsExtension =  window.__REDUX_DEVTOOLS_EXTENSION__;
  if (typeof devToolsExtension === 'function') {
    enhancers.push(devToolsExtension());
  }
}

const store = createStore(
  rootReducer(history),
  initialState,
  compose(

    applyMiddleware(...middleware),
    ...enhancers
  )
);

export default store;
