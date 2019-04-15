/// A REST endpoint controller implementation class for disseminators.
/**
 * DisseminatorController implements the interface defined by Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        disseminator_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        February, 2019
 */
#ifndef DISSEMINATOR_CONTROLLER_H
#define DISSEMINATOR_CONTROLLER_H
#include <controller.hpp>
#include "disseminator_dao_interface.hpp"
using cadg_rest::DisseminatorDaoInterface;

namespace cadg_rest {
class DisseminatorController: public Controller {
  public: 
    DisseminatorController(DisseminatorDaoInterface& dao__) : dao__(dao__) { }
    ~DisseminatorController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    /// Returns the requested disseminator(s).
    /**
     * HandleGet will return a disseminator or collection of disseminators determined
     * by the parameters in the url path.
     * 
     * GET at root path returns all disseminators.<br>
     * `/v1/cadg/api/disseminators/`<br>
     * Success -> 200: 'OK'<br>
     * Failure -> 400: 'Bad Request'
     * 
     * GET with disseminator id (integer) in the path returns
     * an disseminator with that id, or no disseminator if there isn't one.<br>
     * `/v1/cadg/api/disseminators/{id}`
     * 
     * GET with a query for username returns disseminators with that partially
     * or fully match that name.<br>
     * `/v1/cadg/api/disseminators?name={name}`<br>
     * Success -> 200: 'OK'<br>
     * Failure -> 400: 'Bad Request'
     * 
     * @param message The http request to be parsed.
     */
    void HandleGet(http_request message) override;
    /// Updates a current disseminator's data.
    /**
     * NOTE: Not Implemented<br>
     * HandlePut will update a disseminator's data if one exists.<br>
     * The disseminator id should be at the end of the url path.<br>
     * The disseminator's new data should be in the body as json.
     * 
     * `/v1/cadg/api/disseminators/{id}`<br>
     * ```
        {
          "name": "AT&T",
          "type": "CMSP",
          "format": "CMAC",
          "ip": "127.0.0.1",
          "port": 443,
          "backup_port": 4443,
          "status": "ACTIVE"
        }
     * ```
     *    Success -> 204: 'No Content'<br>
     *    Failure -> 400: 'Bad Request'
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePut(http_request message) override;
    /// Creates a new disseminator.
    /**
     * HandlePost will add a new disseminator or collection of disseminators to this endpoint.
     * The body should include json of the disseminators to be posted.
     * 
     * `/v1/cadg/api/disseminators/`<br>
     * ```
        {
          "name": "AT&T",
          "type": "CMSP",
          "format": "CMAC",
          "ip": "127.0.0.1",
          "port": 443,
          "backup_port": 4443,
          "status": "ACTIVE"
        }
     * ```
     *    Success -> 204: 'No Content'<br>
     *    Failure -> 400: 'Bad Request'
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePost(http_request message) override;
    /// Removes an existing disseminator.
    /**
     * NOTE: Not Implemented<br>
     * HandleDelete will delete a disseminator's data if one exists.<br>
     * The disseminator id should be at the end of the url path.
     * 
     * `/v1/cadg/api/disseminators/{id}`
     * 
     * @param message The http request message to be parsed.
     */
    void HandleDelete(http_request message) override;
  private:
    DisseminatorDaoInterface& dao__;
};
}
#endif // DISSEMINATOR_CONTROLLER_H