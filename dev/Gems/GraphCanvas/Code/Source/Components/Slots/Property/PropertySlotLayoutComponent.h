/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <QGraphicsLinearLayout>
#include <qtimer.h>

#include <Components/Slots/SlotLayoutComponent.h>
#include <GraphCanvas/Components/SceneBus.h>
#include <GraphCanvas/Components/StyleBus.h>
#include <GraphCanvas/Components/Slots/SlotBus.h>
#include <GraphCanvas/Components/Slots/Data/DataSlotBus.h>
#include <GraphCanvas/Components/VisualBus.h>
#include <Widgets/GraphCanvasLabel.h>
#include <Widgets/NodePropertyDisplayWidget.h>
#include <Styling/StyleHelper.h>

namespace GraphCanvas
{
    class PropertySlotLayoutComponent;    
    class GraphCanvasLabel;

    class PropertySlotLayout
        : public QGraphicsLinearLayout
        , public SlotNotificationBus::Handler
        , public SceneMemberNotificationBus::Handler
        , public StyleNotificationBus::Handler
        , public VisualNotificationBus::Handler
    {    
    public:
        AZ_CLASS_ALLOCATOR(PropertySlotLayout, AZ::SystemAllocator, 0);

        PropertySlotLayout(PropertySlotLayoutComponent& owner);
        ~PropertySlotLayout();

        void Activate();
        void Deactivate();

        // SceneMemberNotificationBus
        void OnSceneSet(const AZ::EntityId&) override;
        void OnSceneReady() override;
        ////

        // SlotNotificationBus
        void OnRegisteredToNode(const AZ::EntityId& nodeId) override;
        
        void OnTooltipChanged(const TranslationKeyedString& tooltip);
        ////
        
        // StyleNotificationBus
        void OnStyleChanged() override;
        ////
        
    private:

        void TryAndSetupSlot();
    
        void CreateDataDisplay();
        void UpdateLayout();
        void UpdateGeometry();
        
        ConnectionType m_connectionType;
    
        Styling::StyleHelper m_style;
        PropertySlotLayoutComponent& m_owner;
        
        QGraphicsWidget*                                m_spacer;
        NodePropertyDisplayWidget*                      m_nodePropertyDisplay;
        GraphCanvasLabel*                               m_slotText;

        QGraphicsLayoutItem*                            m_layoutItem;
    };    

    //! Lays out the parts of the Data Slot
    class PropertySlotLayoutComponent
        : public SlotLayoutComponent
    {
    public:
        AZ_COMPONENT(PropertySlotLayoutComponent, "{B9F55349-7CAD-49BE-A9D1-F41A89A28024}");
        static void Reflect(AZ::ReflectContext* context);

        PropertySlotLayoutComponent();
        virtual ~PropertySlotLayoutComponent() = default;
        
        void Init();
        void Activate();
        void Deactivate();

    private:
        PropertySlotLayout* m_layout;
    };
}