import React from 'react';
import Jumbotron from 'react-bootstrap/Jumbotron'
import Button from 'react-bootstrap/Button';

const Home = () => {
  return (
    <div className='full-height'>
      <br/><br/>
      {/*<Container>*/}
      <Jumbotron>
        <h1 className='display-4'>Centralized Aggregator and Dissemination Gateway</h1>
        <p className='lead'>
            Welcome to the CADG Control Panel! This panel is for managing data,
            controlling configurations, and monitoring alert activity.
        </p>
        <hr className='my-2'/>
        <p>
          Use the links above to access data for alerts, originator
          groups, disseminators, and other administrators.
        </p>
        <p className='lead'>
          <Button variant='dark'>Learn more</Button>
        </p>
      </Jumbotron>
      {/*</Container>*/}
    </div>
  );
};

export default Home;