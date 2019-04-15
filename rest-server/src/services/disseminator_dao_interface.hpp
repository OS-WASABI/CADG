// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// An interface for a Disseminator DAO.
/**
 * This defines the interface for a data access object (DAO) which is
 * used to provide CRUD operations on a data store of Disseminators.
 *
 * @file        disseminator_dao_interface.hpp
 * @authors     Michael McCulley, Kristofer Hoadley
 * @date        March, 2019
 */
#ifndef DISSEMINATOR_DAO_INTERFACE_H
#define DISSEMINATOR_DAO_INTERFACE_H
#include <optional>
#include <string>
#include <vector>
#include "disseminator.hpp"

namespace cadg_rest {
/// Interface defining what operations a disseminator data access object must implement.
/**
 * DataAccessInterface defines several CRUD operations for a disseminator data store.
 * This interface must be defined in an inheriting class.
 */
class DisseminatorDaoInterface {
  public:
    /**
     * GetDisseminators gets all disseminators in the data store.
     * If unsuccesful, the returned Optional will contain nothing.
     * 
     * @return Optional Vector of all disseminators.
     */
    virtual std::optional<std::vector<Disseminator>> GetDisseminators() = 0;
    /**
     * GetDisseminatorsByName gets all disseminators in the data store which have a name that
     * partially or fully matches the name argument.
     * If unsuccesful, the returned Optional will contain nothing.
     * Returning nothing indicates an inability to connect to the data store.
     * 
     * @param name The name of the disseminator(s) to search for.
     * @return Optional Vector of all disseminators that match the name.
     */
    virtual std::optional<std::vector<Disseminator>> GetDisseminatorsByName(const std::string& name) = 0;
    /**
     * GetDisseminatorByID gets the disseminator in the data store by id.
     * If unsuccesful, the returned Optional will contain nothing.
     * Returning nothing indicates an inability to connect to the data store.
     * 
     * @param id The id of the disseminator to return.
     * @return Optional Vector containing the found disseminator, or empty if there is no matching disseminator.
     */
    virtual std::optional<std::vector<Disseminator>> GetDisseminatorByID(int id) = 0;
    /**
     * RemoveDisseminator removes the disseminator in the data store by id.
     * If unsuccesful, the returned Optional will contain nothing.
     * Returning nothing is different than returning false. False might indicate
     * there is not a disseminator with the provided ID while nothing
     * indicates an inability to connect to the data store.
     * 
     * @param id The id of the disseminator to remove.
     * @return Optional Bool indicating successful removal of disseminator.
     */
    virtual std::optional<bool> RemoveDisseminator(int id) = 0;
    /**
     * AddDisseminator adds the disseminator to the data store.
     * If unsuccesful, the returned Optional will contain nothing.
     * Returning nothing is different than returning false. False might indicate
     * the provided disseminator is invalid or missing fields, while nothing
     * indicates an inability to connect to the data store.
     * 
     * 
     * @param disseminator The disseminator to add to the data store.
     * @return Optional Bool indicating successful addition of disseminator.
     */
    virtual std::optional<bool> AddDisseminator(Disseminator disseminator) = 0;
    /**
     * UpdateDisseminator updates a disseminator in the data store.
     * If unsuccesful, the returned Optional will contain nothing.
     * Returning nothing is different than returning false. False might indicate
     * the provided disseminator is invalid, missing fields, or a corresponding ID
     * was not found, while nothing indicates an inability to connect to the data store.
     * 
     * @param disseminator The updated information for the disseminator.
     * @return Optional Bool indicating a successful update of the disseminator.
     */
    virtual std::optional<bool> UpdateDisseminator(Disseminator disseminator) = 0;
};
}
#endif // DISSEMINATOR_DAO_INTERFACE_H
