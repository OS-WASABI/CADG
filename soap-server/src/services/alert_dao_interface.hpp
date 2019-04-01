/// An interface for an alert data access object.
/**
 * AlertDaoInterface defines the interface for the data access object
 * that will provide CRUD operations on the data storage of alerts.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert_dao_interface.hpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#ifndef ALERT_DAO_INTERFACE_H
#define ALERT_DAO_INTERFACE_H
#include <optional>
#include <string>
#include <vector>
#include "alert.hpp"

namespace cadg_soap {
    /**
     * AlertDaoInterface defines a couple CRUD operations that are to be used on
     * an alert data store. By intention, Alert data can only be retrieved and created.
     * This interface must be defined in an inheriting class.
     */
    class AlertDaoInterface {
    public:
        /// Returns the alert, or collection of alerts, requested.
        /**
         * GetAlerts will return a collection of all alerts in the system.
         * @return
         */
        virtual std::optional<std::vector<Alert>> GetAlerts() = 0;
        /// Returns the alerts sent by the specified originator.
        /**
         * GetAlertsByOriginator returns all alerts with an originator_id that
         * matches the provided id.
         * @param id    The originator_id.
         * @return      Collection of alerts.
         */
        virtual std::optional<std::vector<Alert>> GetAlertsByOriginator(int id) = 0;
        /// Returns all alerts with the specified status.
        /**
         * GetAlertsByStatus returns all alerts that have the specified status.
         * Status can be 'ACTIVE', 'CANCELED', or 'EXPIRED'.
         * @param status    'ACTIVE', 'CANCELED', or 'EXPIRED'.
         * @return          The collection of alerts.
         */
        virtual std::optional<std::vector<Alert>> GetAlertsByStatus(const std::string& status) = 0;
        /// Adds a new alert.
        /**
         * Creates a new alert in the data storage based on the Alert object
         * provided.
         * @param alert The Alert object to add.
         * @return      True if the alert is successfully added.
         */
        virtual std::optional<bool> AddAlert(Alert alert) = 0;
    };
}  // namespace cadg_soap

#endif //ALERT_DAO_INTERFACE_HPP
