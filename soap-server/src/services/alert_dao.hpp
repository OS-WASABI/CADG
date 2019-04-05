/// Implements the interface for an alert data access object.
/**
 * AlertDao implements the interface for the data access object
 * and provides CRUD operations on the data storage of alerts.
 * This DAO is a singleton and should be accessed through the static
 * method, Instance().
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert_dao.hpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */
#ifndef ALERT_DAO_H
#define ALERT_DAO_H
#include "alert_dao_interface.hpp"
#include "logger.hpp"
#include "log_level.hpp"
#include "../model/alert.hpp"

namespace cadg_soap {
    /// A data access object for alerts.
    /**
     * AlertDao implements a couple CRUD operations on the alert data store.
     * By intention, alert data can only be retrived or created.
     */
    class AlertDao : public AlertDaoInterface {
    public:
        /// Returns the AlertDao singleton.
        /**
         * Instance implements the singleton design pattern and returns a reference
         * to the AlertDao.
         * @return  Reference to the AlertDao singleton.
         */
        static AlertDao& Instance();
        /// Deletes the copy constructor to enforce the singleton design pattern.
        AlertDao(AlertDao const&) = delete;
        /// Deletes the assignment constructor to enforce the singleton design pattern.
        void operator = (AlertDao const&) = delete;

        std::optional<std::vector<Alert>> GetAlerts() override;
        std::optional<std::vector<Alert>> GetAlertsByOriginator(int id) override;
        std::optional<std::vector<Alert>> GetAlertsByStatus(const std::string& status) override;
        std::optional<bool> AddAlert(Alert alert) override;
    private:
        /// Returns the environment variable for the specified key
        /**
         * Returns the assigned value to the environment variable with the
         * specified key. If no value exists, a blank value is created.
         * @param key   The environment variable to get.
         * @return      The value of the environment variable.
         */
        std::string getEnvVar(std::string const& key) {
            char const* val = getenv(key.c_str());
            return val == NULL ? std::string() : std::string(val);
        }
        AlertDao();
        std::string conn_str__;
        std::string db_alert_table__;
        LoggerInterface& logger;
    };
}  // namespace cadg_soap
#endif //CADG_REST_SERVER_ALERT_DAO_HPP
