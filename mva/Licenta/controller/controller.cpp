#include "controller.h"

Controller::Controller(): m_pBatteryStatus(NULL), m_pApplicationManager(NULL),
    m_pDMIManager(NULL), m_pSmartManager(NULL), m_pSystemDriversManager(NULL),
    m_pActiveConnectionsManager(NULL), m_pNetworkDevicesManager(NULL), m_pCPUIDManager(NULL),
    m_pSensorsManager(NULL), m_pSensor(NULL), m_pSensorsTimer(NULL)
{
    m_pSensorsTimer = new QTimer(this);
    connect(m_pSensorsTimer, SIGNAL(timeout()), this, SLOT(OnSensorsOptClickedSlot()), Qt::QueuedConnection);

    connect(this, SIGNAL(OnCancelSensorsTimerSignal()), this, SLOT(OnCancelSensorsTimerSlot()), Qt::QueuedConnection);
}

Controller::~Controller()
{
    if (m_pBatteryStatus)
        delete m_pBatteryStatus;
    if (m_pApplicationManager)
        delete m_pApplicationManager;
    if (m_pDMIManager)
        delete m_pDMIManager;
    if (m_pSmartManager)
        delete m_pSmartManager;
    if (m_pSystemDriversManager)
        delete m_pSystemDriversManager;
    if (m_pActiveConnectionsManager)
        delete m_pActiveConnectionsManager;
    if (m_pNetworkDevicesManager)
        delete m_pNetworkDevicesManager;
    if (m_pCPUIDManager)
        delete m_pCPUIDManager;
    if (m_pSensorsManager)
    {
        m_pSensorsManager->DestroySensor();
        delete m_pSensorsManager;
    }
}

void Controller::StartController()
{
    // Create main window
    emit OnCreateMainWindowSignal();

    // Populate left menu tree
    QStandardItemModel *pModel = new QStandardItemModel();
    QStandardItem *pDataRoot = pModel->invisibleRootItem();
    QStandardItem *pDataItem = 0;
    QStandardItem *pChildItem = 0;
    QList<QStandardItem*> qList;
    QList<QStandardItem*> qChildList;

    pDataItem = new QStandardItem(QString("Computer"));
    qList.append(pDataItem);

    pChildItem = new QStandardItem(QString("DMI"));
    qChildList.append(pChildItem);
    pChildItem = new QStandardItem(QString("Power management"));
    qChildList.append(pChildItem);
    pChildItem = new QStandardItem(QString("Sensors"));
    qChildList.append(pChildItem);


    pDataItem->appendRows(qChildList);
    qChildList.clear();

    pDataItem = new QStandardItem(QString("Motherboard"));
    qList.append(pDataItem);

    pChildItem = new QStandardItem(QString("CPU"));
    qChildList.append(pChildItem);
    pChildItem = new QStandardItem(QString("CPUID"));
    qChildList.append(pChildItem);

    pDataItem->appendRows(qChildList);
    qChildList.clear();

    pDataItem = new QStandardItem(QString("Operating system"));
    qList.append(pDataItem);

    pChildItem = new QStandardItem(QString("Operating system"));
    qChildList.append(pChildItem);
    pChildItem = new QStandardItem(QString("Processes"));
    qChildList.append(pChildItem);
    pChildItem = new QStandardItem(QString("System drivers"));
    qChildList.append(pChildItem);

    pDataItem->appendRows(qChildList);
    qChildList.clear();

    pDataItem = new QStandardItem(QString("Storage"));
    qList.append(pDataItem);

    pChildItem = new QStandardItem(QString("ATA"));
    qChildList.append(pChildItem);

    pChildItem = new QStandardItem(QString("SMART"));
    qChildList.append(pChildItem);

    pDataItem->appendRows(qChildList);
    qChildList.clear();

    pDataItem = new QStandardItem(QString("Network"));
    qList.append(pDataItem);

    pChildItem = new QStandardItem(QString("Network devices"));
    qChildList.append(pChildItem);

    pChildItem = new QStandardItem(QString("Connections"));
    qChildList.append(pChildItem);

    pDataItem->appendRows(qChildList);
    qChildList.clear();

    pDataItem = new QStandardItem(QString("Software"));
    qList.append(pDataItem);

    pChildItem = new QStandardItem(QString("Startup applications"));
    qChildList.append(pChildItem);
    pChildItem = new QStandardItem(QString("Application manager"));
    qChildList.append(pChildItem);

    pDataItem->appendRows(qChildList);
    qChildList.clear();

    pDataRoot->appendRows(qList);
    qList.clear();

    emit OnPopulateMenuTreeSignal(pModel);

    emit OnShowMainWindowSignal();

    // Create Sensor Object
    m_pSensorsManager = new CSensorModule;
    m_pSensor = m_pSensorsManager->DetectSensor();
    if (m_pSensor)
        m_pSensor->Initialize();
}

void Controller::OnComputerDMIOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    // delete previous object
    SAFE_DELETE(m_pDMIManager);

    m_pDMIManager = new CSMBiosEntryPoint;

    CHECK_ALLOCATION(m_pDMIManager);

    QStandardItemModel *pModel = m_pDMIManager->GetItemsModel();

    if (0 != pModel)
        emit OnSetDMIItemsInformation(pModel);
}

void Controller::OnComputerPowerManagementOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    // delete previous object
    SAFE_DELETE(m_pBatteryStatus);

    m_pBatteryStatus = new BatteryStatus;

    CHECK_ALLOCATION(m_pBatteryStatus);

    QStandardItemModel *pModel = m_pBatteryStatus->GetBatteryInformation();

    if (0 != pModel)
        emit OnSetPowerManagementInformation(pModel);
}

void Controller::OnHddInformationOptClickedSlot()
{
    qDebug() << __FUNCTION__;
}

void Controller::OnOperatingSystemOptClickedSlot()
{
    qDebug() << __FUNCTION__;
}

void Controller::OnProcessesOptClickedSlot()
{
    qDebug() << __FUNCTION__;
}

void Controller::OnSystemDriversOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    // delete previous object
    SAFE_DELETE(m_pSystemDriversManager);

    m_pSystemDriversManager = new SystemDrivers;

    CHECK_ALLOCATION(m_pSystemDriversManager);

    QStandardItemModel *pModel = m_pSystemDriversManager->GetSystemDriversInformation();

    if( 0 != pModel )
        emit OnSetSystemDriversModelInformation(pModel);
}

void Controller::OnStorageATAOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    QStandardItemModel *pModel = new QStandardItemModel();
    QStringList List = GetPhysicalDrivesList();

    pModel->setColumnCount(1);
    pModel->setRowCount(List.count());
    pModel->setHorizontalHeaderLabels(QStringList() << "Device description");
    for(int i = 0; i < List.count(); i++)
    {
        ATADeviceProperties *pProp = GetATADeviceProperties(List.at(i).toStdWString().c_str());
        if (NULL == pProp)
            continue;
        m_HDDModelToPhysicalDrive.insert(pProp->Model, List.at(i));
        pModel->setItem(i, 0, new QStandardItem(pProp->Model));
        delete pProp;
    }

    emit OnSetATAHDDItemsInformation(pModel);
}

void Controller::OnStorageSmartOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    // delete previous object
    SAFE_DELETE(m_pSmartManager);

    m_pSmartManager = new CSmartInfo();

    CHECK_ALLOCATION(m_pSmartManager);

    QStandardItemModel *pModel = m_pSmartManager->GetAvailableHDD();

    if (0 != pModel)
        emit OnSetSMARTHDDItemsInformation(pModel);
}

void Controller::OnSmbiosOptClickedSlot()
{
    qDebug() << __FUNCTION__;
}

void Controller::OnApplicationManagerOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    // delete  previous object
    SAFE_DELETE(m_pApplicationManager);

    m_pApplicationManager = new CApplicationManager();

    CHECK_ALLOCATION(m_pApplicationManager);

    QStandardItemModel *pModel = m_pApplicationManager->GetApplicationList();

    if (0 != pModel)
        emit OnSetApplicationManagerInformation(pModel);
}

void Controller::OnStartupApplicationsOptClickedSlot()
{
    qDebug() << __FUNCTION__;
}

void Controller::OnActiveConnectionsOptClickedSlot()
{
    // cancel all timers
    emit OnCancelSensorsTimerSignal();

    SAFE_DELETE(m_pActiveConnectionsManager);

    m_pActiveConnectionsManager = new CActiveConnections;

    CHECK_ALLOCATION(m_pActiveConnectionsManager);

    QStandardItemModel *pModel = m_pActiveConnectionsManager->GetActiveConnections();

    if (0 != pModel)
        emit OnSetActiveConnectionsInformation(pModel);
}

void Controller::OnNetworkDevicesOptClickedSlot()
{
    emit OnCancelSensorsTimerSignal();

    SAFE_DELETE(m_pNetworkDevicesManager);

    m_pNetworkDevicesManager = new CNetworkDevices;

    CHECK_ALLOCATION(m_pNetworkDevicesManager);

    QStandardItemModel *pModel = m_pNetworkDevicesManager->GetAdapterNames();

    if (0 != pModel)
        emit OnSetNetworkDevicesNames(pModel);
}

void Controller::OnCPUOptClickedSlot()
{

}

void Controller::OnCPUIDOptClickedSlot()
{
    emit OnCancelSensorsTimerSignal();

    SAFE_DELETE(m_pCPUIDManager);

    m_pCPUIDManager = new CIntelCpuID;

    CHECK_ALLOCATION(m_pCPUIDManager);

    QStandardItemModel *pModel = m_pCPUIDManager->GetCPUIDInformations();

    if (0 != pModel )
        emit OnSetCPUIDInformations(pModel);
}

void Controller::OnSensorsOptClickedSlot()
{
    SensorsData *pSensorData = new SensorsData;
    CHECK_ALLOCATION(pSensorData);

    DataType *pDataType;
    ItemPair *pItemPair;
    MotherboardData *pMBData;
    CpuData *pCpuData;

    double *pResults = 0;

    if (!m_pSensorsTimer->isActive())
        m_pSensorsTimer->start(750);

    if (!m_pSensor)
        return;

    pMBData = pSensorData->mutable_mbdata();
    pMBData->set_name(m_pSensor->GetChipName().toLatin1().data());

    m_pSensor->Update();
    pResults = m_pSensor->GetTemps();

    pDataType = pMBData->add_data();
    pDataType->set_dataname("Temperatures: ");

    QString qzTemp1 = "", qzTemp2 = "";
    for(int i = 0; i < 3; i++)
    {
        if (!pResults[i])
            continue;
        qzTemp1.sprintf("Temperature #%d", i + 1);
        qzTemp2.sprintf("%.1fC", pResults[i]);

        pItemPair = pDataType->add_datavalue();
        pItemPair->set_name(qzTemp1.toLatin1().data());
        pItemPair->set_value(qzTemp2.toLatin1().data());
    }

    // voltages
    pDataType = pMBData->add_data();
    pDataType->set_dataname("Voltages: ");

    pResults = m_pSensor->GetVoltages();

    for(int i = 0; i < 9; i++)
    {
        if (!pResults[i])
            continue;
        qzTemp1.sprintf("Voltage #%d", i + 1);
        qzTemp2.sprintf("%.1fC", pResults[i]);

        pItemPair = pDataType->add_datavalue();
        pItemPair->set_name(qzTemp1.toLatin1().data());
        pItemPair->set_value(qzTemp2.toLatin1().data());
    }

    // fan speed
    pDataType = pMBData->add_data();
    pDataType->set_dataname("Fan speed: ");

    pResults = m_pSensor->GetFanSpeeds();

    for(int i = 0; i < 5; i++)
    {
        if (!pResults[i])
            continue;
        qzTemp1.sprintf("Fan #%d", i + 1);
        qzTemp2.sprintf("%.1fRPM", pResults[i]);

        pItemPair = pDataType->add_datavalue();
        pItemPair->set_name(qzTemp1.toLatin1().data());
        pItemPair->set_value(qzTemp2.toLatin1().data());
    }

    pCpuData = pSensorData->mutable_cpudata();
    pCpuData->set_name(m_pSensorsManager->GetCpuName().toLatin1().data());

    pDataType = pCpuData->add_data();
    pDataType->set_dataname("Usage: ");

    pItemPair = pDataType->add_datavalue();
    pItemPair->set_name("CPU0");
    pItemPair->set_value(QString().sprintf("%.2f%", m_pSensorsManager->GetCpuLoad()).toLatin1().data());

    std::string tempString= pSensorData->SerializeAsString();

    emit OnSetSensorsInformations(tempString);
}

void Controller::OnRequestDMIItemProperties(DMIModuleType ItemType)
{
    QStandardItemModel *pModel = m_pDMIManager->GetItemPropertiesModel(ItemType);

    if (0 != pModel)
        emit OnSetDMIPropertiesInfomation(pModel);
}

void Controller::OnRequestATAItemProperties(QString qzModel)
{
    QString qzDrive = m_HDDModelToPhysicalDrive.value(qzModel);
    ATADeviceProperties *pProp = GetATADeviceProperties(qzDrive.toStdWString().c_str());
    CHECK_ALLOCATION(pProp);

    QStandardItemModel *pModel = new QStandardItemModel();
    QStandardItem *pItem = 0;

    pModel->setColumnCount(2);
    pModel->setRowCount(15);
    pModel->setHorizontalHeaderLabels(QStringList() << "Field" << "Value");

    pItem = new QStandardItem("Model:");
    pModel->setItem(0, 0, pItem);
    pItem = new QStandardItem(pProp->Model);
    pModel->setItem(0, 1, pItem);
    pItem = new QStandardItem("Firmware revision:");
    pModel->setItem(1, 0, pItem);
    pItem = new QStandardItem(pProp->FirmwareRevision);
    pModel->setItem(1, 1, pItem);
    pItem = new QStandardItem("Serial number:");
    pModel->setItem(2, 0, pItem);
    pItem = new QStandardItem(pProp->SerialNumber);
    pModel->setItem(2, 1, pItem);
    pItem = new QStandardItem("Rotation speed:");
    pModel->setItem(3, 0, pItem);
    pItem = new QStandardItem(pProp->RotationSpeed);
    pModel->setItem(3, 1, pItem);
    pItem = new QStandardItem("Buffer size:");
    pModel->setItem(4, 0, pItem);
    pItem = new QStandardItem(pProp->BufferSize);
    pModel->setItem(4, 1, pItem);
    pItem = new QStandardItem("Type:");
    pModel->setItem(5, 0, pItem);
    pItem = new QStandardItem(pProp->DeviceType);
    pModel->setItem(5, 1, pItem);
    pItem = new QStandardItem("Cylinders:");
    pModel->setItem(6, 0, pItem);
    pItem = new QStandardItem(pProp->Cylinders);
    pModel->setItem(6, 1, pItem);
    pItem = new QStandardItem("Heads:");
    pModel->setItem(7, 0, pItem);
    pItem = new QStandardItem(pProp->Heads);
    pModel->setItem(7, 1, pItem);
    pItem = new QStandardItem("Sectors per track:");
    pModel->setItem(8, 0, pItem);
    pItem = new QStandardItem(pProp->SectorPerTrack);
    pModel->setItem(8, 1, pItem);
    pItem = new QStandardItem("Bytes per sector:");
    pModel->setItem(9, 0, pItem);
    pItem = new QStandardItem(pProp->BytesPerSector);
    pModel->setItem(9, 1, pItem);
    pItem = new QStandardItem("ATA standard:");
    pModel->setItem(10, 0, pItem);
    pItem = new QStandardItem(pProp->ATAStandard);
    pModel->setItem(10, 1, pItem);
    pItem = new QStandardItem("UDMA transfer mode:");
    pModel->setItem(11, 0, pItem);
    pItem = new QStandardItem(pProp->UDMATransferMode);
    pModel->setItem(11, 1, pItem);
    pItem = new QStandardItem("Active UDMA transfer mode:");
    pModel->setItem(12, 0, pItem);
    pItem = new QStandardItem(pProp->ActiveUDMATransferMode);
    pModel->setItem(12, 1, pItem);
    pItem = new QStandardItem("PIO transfer mode");
    pModel->setItem(13, 0, pItem);
    pItem = new QStandardItem(pProp->PIOTransferMode);
    pModel->setItem(13, 1, pItem);
    pItem = new QStandardItem("MWDMA transfer mode:");
    pModel->setItem(14, 0, pItem);
    pItem = new QStandardItem(pProp->MWDMATransferMode);
    pModel->setItem(14, 1, pItem);

    emit OnSetATAItemPropertiesInformation(pModel);
}

void Controller::OnRequestSMARTProperties(QString qzModel)
{
    QStandardItemModel *pModel = m_pSmartManager->GetSMARTPropertiesForHDD(qzModel);

    if (0 != pModel)
        emit OnSetSMARTItemPropertiesInformation(pModel);
}

void Controller::OnUninstallApplicationSlot()
{
    qDebug() << __FUNCTION__;
}

void Controller::OnRequestNetworkDeviceInfomationsSlot(QString qzAdapterName)
{
    if (m_pNetworkDevicesManager)
    {
       QStandardItemModel *pModel = m_pNetworkDevicesManager->GetAdapterInformations(qzAdapterName);

       if (pModel)
           emit OnSetNetworkDeviceInformation(pModel);
    }
}

void Controller::OnCancelSensorsTimerSlot()
{
    m_pSensorsTimer->stop();
}
