/// A DAO for disseminators.
/**
 * This data access object adheres to the DisseminatorDaoInterface. It is a singleton,
 * accessed through the static method Instance(). The data store is backed by a MySQL
 * database, using nanodbc to make database queries.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        disseminator_dao.hpp
 * @authors     Michael McCulley, Kristofer Hoadley
 * @date        March, 2019
 */
#ifndef DISSEMINATOR_DAO_H
#define DISSEMINATOR_DAO_H
#include <string>
#include <vector>
#include "disseminator_dao_interface.hpp"
#include "logger.hpp"
#include "log_level.hpp"

namespace cadg_rest {
/// An implementation of the Disseminator DAO interface using a MySQL database as a data store.
class DisseminatorDao : public DisseminatorDaoInterface {
  public:
    /// Instance returns a reference to the DisseminatorDao, enforcing singleton.
    static DisseminatorDao& Instance();
    /// Deletes the copy constructor to enforce singleton.
    DisseminatorDao(DisseminatorDao const&) = delete;
    /// Deletes the assignment constructor to enforce singleton.
    void operator=(DisseminatorDao const&) = delete;
    std::optional<std::vector<Disseminator>> GetDisseminators() override;
    std::optional<std::vector<Disseminator>> GetDisseminatorsByName(const std::string& name) override;
    std::optional<std::vector<Disseminator>> GetDisseminatorByID(int id) override;
    std::optional<bool> RemoveDisseminator(int id) override;
    std::optional<bool> AddDisseminator(Disseminator disseminator) override;
    std::optional<bool> UpdateDisseminator(Disseminator disseminator) override;
    
  private:
    DisseminatorDao();
    std::vector<Disseminator> disseminators__;
    std::string conn_str__;
    std::string db_disseminators_table__;
    LoggerInterface& logger__;
    /// Get the host environment variable with a given key.
    /**
     * Get the host environment variable with a given key.
     * If key doens't exist, returns an empty string.
     * 
     * @param key of the environment variable to get.
     * @return Value of the environment variable.
     */
    std::string getEnvVar(std::string const& key) {
        char const* val = getenv(key.c_str()); 
        return val == NULL ? std::string() : std::string(val);
    }
    /// Refreshes locally cached data from data store.
    /**
     * Requery gets all disseminators from the data store and caches them locally.
     * This should be done each time the locally cached data may be out of sync
     * with the data store.
     * Currently it is done each time there is a GET request. The assumption being
     * there will be more than one Disseminator DAO interacting with the data store.
     * The intention is to reduce the number of data store loads, but this still needs
     * to be optimized.
     * 
     * @return Bool indicating if cached data was updated.
     */
    bool Requery();
};
}
#endif // DISSEMINATOR_DAO_H
