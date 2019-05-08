import React, { Component } from 'react';
import Table from 'react-bootstrap/Table';
import Container from 'react-bootstrap/Container'
import Button from 'react-bootstrap/Button';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import { connect } from 'react-redux';
import AddAdmin from './add-admin-modal'

class Admins extends Component {
  constructor(props) {
    super(props);
    this.state = {
      isAdding: false
    };
    this.toggleAdding = this.toggleAdding.bind(this);
    this.getAdmin = this.getAdmin.bind(this);
  }

  toggleAdding() {
    this.setState(prevState => ({
      ...prevState,
      isAdding: !prevState.isAdding
    }));
  }

  getAdmin() {
   return (
     Object.keys(this.props.admins).map((id) => {
       if(id >= 0){
         return (
           <tr key={id} style={{'fontSize':'small'}}>
             <th scope='row'>{id}</th>
             <td>{this.props.admins[id].username}</td>
             <td>{this.props.admins[id].first_name}</td>
             <td>{this.props.admins[id].last_name}</td>
             <td>{this.props.admins[id].email}</td>
             <td>{this.props.admins[id].phone}</td>
             <td>
               {this.props.admins[id].address} {this.props.admins[id].state_region} {this.props.admins[id].country} {this.props.admins[id].zip}
             </td>
           </tr>
         );
       }
       else return null;
     })
   )
  }

  render() {
    return (
      <div>
        <br/><br/><br/><br/>
        <Container fluid>
          <Row>
            <Col>
              <h1>Administrators</h1>
            </Col>
            <Col align='right'>
              <Button size='lg' color='primary' onClick={this.toggleAdding}>+</Button>{' '}
            </Col>
          </Row>
          <br/>
          <Table hover responsive size='sm'>
            <thead style={{'fontSize':'medium'}}>
            <tr>
              <th>ID#</th>
              <th>Username</th>
              <th>First</th>
              <th>Last</th>
              <th>Email</th>
              <th>Phone</th>
              <th>Address</th>
            </tr>
            </thead>
            <tbody>
            {this.getAdmin()}
            </tbody>
          </Table>
        </Container>
        <AddAdmin isAdding={this.state.isAdding} toggle={() => this.toggleAdding()}/>
      </div>
    );
  }
}

const mapStateToProps = state => ({
  admins: state.admins.admins
})


export default connect(mapStateToProps, null)(Admins);