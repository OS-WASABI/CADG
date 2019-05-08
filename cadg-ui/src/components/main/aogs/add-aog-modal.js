import React, { Component } from 'react';
import ButtonGroup from 'react-bootstrap/ButtonGroup'
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import Col from 'react-bootstrap/Col'

export default class Admins extends Component {
  constructor(props) {
    super(props);
    this.state = {
      selected: ''
    }
    this.onRadioBtnClick = this.onRadioBtnClick.bind(this);
  }

  onRadioBtnClick(rSelected) { this.setState({ selected: rSelected }); }

  render() {
    return (
      <div>
        <Form.Row>
        <Modal show={this.props.isAdding} onHide={this.props.toggle}>
          <Modal.Header closeButton>
            <Modal.Title>
              Add Alert Originator Group
            </Modal.Title>
          </Modal.Header>
          <Modal.Body>
            <Form.Row>
              <Col>
                <Form.Group controlId='originator_name'>
                  <Form.Control placeholder='Group name' type='text'/>
                </Form.Group>
              </Col>
              <Col md={6}>
                <Form.Group controlId='status'>
                  <ButtonGroup>
                    <Button
                      variant='outline-warning'
                      onClick={() => this.onRadioBtnClick('ACTIVE')}
                      active={this.state.selected==='ACTIVE'}
                    >ACTIVE</Button>
                    <Button
                      variant={'outline-secondary'}
                      onClick={() => this.onRadioBtnClick('DISABLED')}
                      active={this.state.selected==='DISABLED'}
                    >DISABLED</Button>
                  </ButtonGroup>
                </Form.Group>
              </Col>
            </Form.Row>

            <Form.Group  controlId='agency'>
              <Form.Control placeholder='Agency' type='text'/>
            </Form.Group>

          </Modal.Body>
          <Modal.Footer>
            <Button variant="outline-primary">Submit</Button>{' '}
            <Button variant="light" onClick={this.props.toggle}>Cancel</Button>
          </Modal.Footer>
        </Modal>
        </Form.Row>
      </div>
    );
  }
}
