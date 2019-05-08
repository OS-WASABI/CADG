import React, { Component } from 'react';
import Navbar from 'react-bootstrap/Navbar';
import Nav from 'react-bootstrap/Nav';
import logo from '../../images/logo.svg';

export default class Header extends Component {
  constructor(props) {
    super(props);

    this.toggle = this.toggle.bind(this);
    this.state = {
      isOpen: false
    };
  }

  toggle() { this.setState({ isOpen: !this.state.isOpen }); }

  render() {
    return (
      <div>
        <Navbar bg="dark" variant="dark" fixed='top' expand="lg">
          <Navbar.Brand href="/">
            <b>OS-WASABI</b> <img src={logo} alt='logo' height='42' width='42'/> CADG
          </Navbar.Brand>
          <Navbar.Toggle onClick={this.toggle} />
          <Navbar.Collapse id="responsive-navbar-nav">
            <Nav className="ml-auto" navbar>

              {/*Alerts*/}
                <Nav.Link href="/alerts"><b>Alerts</b></Nav.Link>

              {/*Originators*/}
                <Nav.Link href="/originators"><b>Originators</b></Nav.Link>

              {/*Disseminators*/}
                <Nav.Link href="/disseminators"><b>Disseminators</b></Nav.Link>

              {/*Admins*/}
                <Nav.Link href="/admins"><b>Administrators</b></Nav.Link>

              {/*Login*/}
                <Nav.Link className='text-white' href="/login"><b>Login</b></Nav.Link>
            </Nav>
          </Navbar.Collapse>
        </Navbar>
      </div>
    );
  }
}