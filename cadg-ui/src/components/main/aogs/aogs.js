import React, { Component } from 'react';
import Table from 'react-bootstrap/Table';
import Container from 'react-bootstrap/Container'
import Button from 'react-bootstrap/Button';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import { connect } from 'react-redux';
import AddAOG from './add-aog-modal'

class AOGs extends Component {
  constructor(props) {
    super(props);
    this.state = {
      isAdding: false
    };
    this.toggleAdding = this.toggleAdding.bind(this);
    this.getAOG = this.getAOG.bind(this);
  }

  toggleAdding() {
    this.setState(prevState => ({
      ...prevState,
      isAdding: !prevState.isAdding
    }));
  }

  getAOG() {
    return (
      Object.keys(this.props.aogs).map((id) => {
        let aog = this.props.aogs[id];
        let color = aog.status === 'ACTIVE' ? 'success' : 'danger';
        return (
          <tr key={id} style={{'fontSize':'small'}}>
            <th scope='row'>{id}</th>
            <td>{aog.originator_name}</td>
            <td color={color}>{aog.status}</td>
            <td>{aog.agency}</td>
          </tr>
        );
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
              <h1>Alert Originator Groups</h1>
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
              <th>Name</th>
              <th>Status</th>
              <th>Agency</th>
            </tr>
            </thead>
            <tbody>
            {this.getAOG()}
            </tbody>
          </Table>
        </Container>
        <AddAOG isAdding={this.state.isAdding} toggle={() => this.toggleAdding()}/>
      </div>
    );
  }
}

const mapStateToProps = state => ({
  aogs: state.aogs.aogs
})


export default connect(mapStateToProps, null)(AOGs);