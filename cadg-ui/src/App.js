import React, { Component } from 'react';
import {
  BrowserRouter as Router,
  Route,
  Switch
} from 'react-router-dom';
import Header from './components/header/header';
import Home from './components/main/home';
import Alerts from './components/main/alerts'
import Originators from './components/main/aogs/aogs';
import Disseminators from './components/main/disseminators';
import Admins from './components/main/admins/admins'

class App extends Component {
  render() {
    return (
      <div className="App">
        <Header/>
        <Router>
          <Switch>
            <Route exact path='/' component={Home}/>
            <Route path='/alerts' component={Alerts}/>
            <Route path='/originators' component={Originators}/>
            <Route path='/disseminators' component={Disseminators}/>
            <Route path='/admins' component={Admins}/>
            <Route component={Home}/>
          </Switch>
        </Router>
      </div>
    );
  }
}

export default App;
