import React, { Component } from 'react';
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup'
import Col from 'react-bootstrap/Col'

export default class Admins extends Component {
  render() {
    return (
      <div>
        <Form>

        <Modal show={this.props.isAdding} onHide={this.props.toggle}>
          <Modal.Header closeButton>
            <Modal.Title>Add Administrator</Modal.Title>
          </Modal.Header>
          <Modal.Body>
            <Form.Row>
              <Col>
                <Form.Group controlId='first_name'>
                  <Form.Control placeholder='First name' type='text'/>
                </Form.Group>
              </Col>
              <Col>
                <Form.Group controlId='last_name'>
                  <Form.Control placeholder='Last name' type='text'/>
                </Form.Group>
              </Col>
            </Form.Row>

            <Form.Row>
              <Col>
                <Form.Group controlId='email'>
                  <Form.Control placeholder='Email' type='email'/>
                </Form.Group>
              </Col>
              <Col>
                <Form.Group controlId='phone'>
                  <Form.Control placeholder='Phone' type='phone'/>
                </Form.Group>
              </Col>
            </Form.Row>

            <Form.Group controlId='username'>
              <InputGroup>
                <InputGroup.Prepend>
                  <InputGroup.Text id="inputGroupPrepend">@</InputGroup.Text>
                </InputGroup.Prepend>
                <Form.Control placeholder='Username' type='text'/>
              </InputGroup>
            </Form.Group>

            <Form.Group controlId='address'>
              <Form.Control placeholder='Address' type='text'/>
            </Form.Group>

            <Form.Row>
              <Col>
                <Form.Control id='city' placeholder='City' type='text'/>
              </Col>
              <Col>
                <Form.Control id='region_state' placeholder='State/Region' type='text'/>
              </Col>
              <Col>
                <Form.Control id='country' placeholder='Country' type='text'/>
              </Col>
              <Col>
                <Form.Control id='zip' placeholder='Zip' type='text'/>
              </Col>
            </Form.Row>

          </Modal.Body>
          <Modal.Footer>
            <Button variant="outline-primary">Submit</Button>{' '}
            <Button variant="light" onClick={this.props.toggle}>Cancel</Button>
          </Modal.Footer>
        </Modal>
        </Form>
      </div>
    );
  }
}
