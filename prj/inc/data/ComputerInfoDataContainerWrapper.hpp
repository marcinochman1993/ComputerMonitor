/*
 * ComputerInfoDataContainerWrapper.hpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFODATACONTAINERWRAPPER_HPP_
#define COMPUTERINFODATACONTAINERWRAPPER_HPP_

#include <QObject>
#include "ComputerInfoDataContainer.hpp"

class ComputerInfoDataContainerWrapper: public QObject, public Info
{
    Q_OBJECT

  public:
    ComputerInfoDataContainerWrapper():QObject(nullptr), m_dataContainer(nullptr) { }
    void data(ComputerInfoDataContainer* dataContainer) { m_dataContainer = dataContainer; }
    const ComputerInfoDataContainer* dataContainer() const { return m_dataContainer; }
    bool update();

  private:
    ComputerInfoDataContainer* m_dataContainer;

    signals:
    void dataUpdated();
    void beforeDataUpdate();
};

#endif /* COMPUTERINFODATACONTAINERWRAPPER_HPP_ */
