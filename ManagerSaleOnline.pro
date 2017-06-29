QT += core gui widgets svg network
TARGET = SaleApp
TEMPLATE = app
CONFIG -= console

CONFIG(debug, debug|release) {
    BUILD_CONFIG = Debug
} else {
    BUILD_CONFIG = Release
}

#Defined common config for all subdirectory .pro file
LIB_DIR = "E:\Git\ZaloPC\FullCode\Lib" # Directory to lib folder
#Trick to replace on Windows
LIB_DIR = $$replace(LIB_DIR, \\\, /)

LIBS += -L"$${LIB_DIR}/openssl/$${BUILD_CONFIG}/lib"
INCLUDEPATH += "$${LIB_DIR}/openssl/$${BUILD_CONFIG}/include"

# [Setup the Dependencies]
DEPEND_TARGET_NAME = 0      # Name of project which has been depended to
DEPEND_TARGET_PATH = 0      # Path to source file of project which has been depended to

for(dep, DEPENDENCY_PROJECT) {
    DEPEND_TARGET_NAME = $${dep}
    $${TARGET}.depends += $${DEPEND_TARGET_NAME}
}

LIBS += -L"$${LIB_DIR}/zlib/$${BUILD_CONFIG}/lib"

INCLUDEPATH += "$${LIB_DIR}/zlib/$${BUILD_CONFIG}/include"

LIBS += -lzlib

SOURCES += \
    SourceCode/main.cpp \
    SourceCode/gui/CustomControl/swidget.cpp \
    SourceCode/gui/smainwindow.cpp \
    SourceCode/ssingleapp.cpp \
    SourceCode/style-sheet-manager.cpp \
    SourceCode/gui/CustomControl/sbuttonoption.cpp \
    SourceCode/gui/CustomControl/stabwidget.cpp \
    SourceCode/gui/page-search.cpp \
    SourceCode/gui/CustomControl/sconstantmenu.cpp \
    SourceCode/gui/CustomControl/page-navigation.cpp \
    SourceCode/core/request/apirequest.cpp \
    SourceCode/core/dataitem/abstract_data_item.cpp \
    SourceCode/core/jsonutil/json_utils.cpp \
    SourceCode/core/jsonutil/json_exception.cpp \
    SourceCode/core/request/iapi_request.cpp \
    SourceCode/core/request/i_api_finish_listener.cpp \
    SourceCode/core/network/http_connection.cpp \
    SourceCode/core/request/request_utils.cpp \
    SourceCode/lazada/lazada_handler.cpp \
    SourceCode/lazada/dataitem/lazada_data_item_list_order.cpp \
    SourceCode/core/utils/api_command_defined.cpp \
    SourceCode/core/service_map_manager.cpp \
    SourceCode/core/request/apirequest_get.cpp \
    SourceCode/lazada/request/lazada_api_request_get.cpp \
    SourceCode/core/request/apirequest_worker.cpp \
    SourceCode/core/network/network_manager_factory.cpp \
    SourceCode/core/network/network_session_manager.cpp \
    SourceCode/core/utils/gzip_utils.cpp \
    SourceCode/core/network/sessionmanager.cpp \
    SourceCode/gui/CustomControl/testingcellui.cpp \
    SourceCode/gui/CustomControl/cache.cpp \
    SourceCode/gui/CustomControl/sitemdelegate.cpp \
    SourceCode/gui/CustomControl/stableview.cpp \
    SourceCode/gui/CustomControl/sfilter-info.cpp \
    SourceCode/gui/CustomControl/flowlayout.cpp \
    SourceCode/gui/CustomControl/verticalscrollbar.cpp \
    SourceCode/lazada/lazada_request_api_factory.cpp \
    SourceCode/lazada/lazada_parser_factory.cpp \
    SourceCode/gui/CustomControl/detailwidget.cpp \
    SourceCode/uimodel.cpp \
    SourceCode/gui/CustomControl/sdialog.cpp \
    SourceCode/gui/CustomControl/svgwidget.cpp \
    SourceCode/lazada/lazada_api_command_defined.cpp \
    SourceCode/lazada/request/lazada_api_request_order_items.cpp \
    SourceCode/lazada/dataitem/lazada_data_item_order_items.cpp \
    SourceCode/lazada/dataitem/lazada_data_item_order.cpp \
    SourceCode/lazada/dataitem/lazada_data_item_bill_order.cpp \
    SourceCode/gui/table-model.cpp \
    SourceCode/ui_executor.cpp \
    SourceCode/gui/leftpanel.cpp \
    SourceCode/signalsender.cpp \
    SourceCode/gui/suserinfo.cpp \
    SourceCode/gui/CustomControl/drop-down-widget.cpp \
    SourceCode/gui/navigationbar.cpp \
    SourceCode/gui/CustomControl/page-ui-manager.cpp \
    SourceCode/gui/CustomControl/date-range-widget.cpp \
    SourceCode/lazada/request/lazada_api_request_set_status_to_canceled.cpp \
    SourceCode/lazada/request/lazada_api_request_set_status_to_packed_by_marketplace.cpp \
    SourceCode/lazada/request/lazada_api_request_set_status_to_ready_to_ship.cpp \
    SourceCode/lazada/request/lazada_api_request_set_invoice_number.cpp \
    SourceCode/lazada/request/lazada_api_request_get_failure_reasons.cpp \
    SourceCode/lazada/request/lazada_api_request_get_document.cpp \
    SourceCode/lazada/request/lazada_api_request_get_shipment_providers.cpp \
    SourceCode/lazada/request/lazada_api_request_get_metrics.cpp \
    SourceCode/lazada/request/lazada_api_request_get_payout_status.cpp \
    SourceCode/lazada/request/lazada_api_request_get_statistics.cpp \
    SourceCode/lazada/request/lazada_api_request_seller_update.cpp \
    SourceCode/lazada/request/lazada_api_request_user_update.cpp \
    SourceCode/lazada/request/lazada_api_request_get_category_attributes.cpp \
    SourceCode/lazada/request/lazada_api_request_get_category_tree.cpp \
    SourceCode/lazada/request/lazada_api_request_get_brands.cpp \
    SourceCode/lazada/request/lazada_api_request_remove_product.cpp \
    SourceCode/lazada/request/lazada_api_request_update_price_quantity.cpp \
    SourceCode/lazada/request/lazada_api_request_create_product.cpp \
    SourceCode/lazada/request/lazada_api_request_update_product.cpp \
    SourceCode/lazada/request/lazada_api_request_set_images.cpp \
    SourceCode/lazada/request/lazada_api_request_migrate_image.cpp \
    SourceCode/lazada/request/lazada_api_request_upload_image.cpp \
    SourceCode/lazada/request/lazada_api_request_search_spus.cpp \
    SourceCode/lazada/request/lazada_api_request_get_products.cpp \
    SourceCode/lazada/request/lazada_api_request_get_orders.cpp \
    SourceCode/lazada/request/lazada_api_request_get_order.cpp \
    SourceCode/gui/CustomControl/table/datahandler.cpp \
    SourceCode/gui/CustomControl/table/tinytablewidget.cpp \
    SourceCode/gui/CustomControl/table/tablecell.cpp \
    SourceCode/gui/CustomControl/horizontalscrollbar.cpp \
        SourceCode/gui/CustomControl/calendar-widget.cpp \
    SourceCode/gui/CustomControl/zbackground-menu.cpp \
    SourceCode/gui/CustomControl/background_menu_utils.cpp \

HEADERS += \
    SourceCode/gui/CustomControl/swidget.h \
    SourceCode/gui/smainwindow.h \
    SourceCode/ssingleapp.h \
    SourceCode/style-sheet-manager.h \
    SourceCode/uiconst.h \
    SourceCode/gui/CustomControl/sbuttonoption.h \
    SourceCode/gui/CustomControl/stabwidget.h \
    SourceCode/gui/page-search.h \
    SourceCode/gui/CustomControl/sconstantmenu.h \
    SourceCode/gui/CustomControl/page-navigation.h \
    SourceCode/core/request/apirequest.h \
    SourceCode/core/dataitem/abstract_data_item.h \
    SourceCode/core/jsonutil/rapidjson/error/en.h \
    SourceCode/core/jsonutil/rapidjson/error/error.h \
    SourceCode/core/jsonutil/rapidjson/internal/biginteger.h \
    SourceCode/core/jsonutil/rapidjson/internal/diyfp.h \
    SourceCode/core/jsonutil/rapidjson/internal/dtoa.h \
    SourceCode/core/jsonutil/rapidjson/internal/ieee754.h \
    SourceCode/core/jsonutil/rapidjson/internal/itoa.h \
    SourceCode/core/jsonutil/rapidjson/internal/pow10.h \
    SourceCode/core/jsonutil/rapidjson/internal/stack.h \
    SourceCode/core/jsonutil/rapidjson/internal/strfunc.h \
    SourceCode/core/jsonutil/rapidjson/internal/strtod.h \
    SourceCode/core/jsonutil/rapidjson/internal/swap.h \
    SourceCode/core/jsonutil/rapidjson/msinttypes/inttypes.h \
    SourceCode/core/jsonutil/rapidjson/msinttypes/stdint.h \
    SourceCode/core/jsonutil/rapidjson/allocators.h \
    SourceCode/core/jsonutil/rapidjson/encodedstream.h \
    SourceCode/core/jsonutil/rapidjson/encodings.h \
    SourceCode/core/jsonutil/rapidjson/filereadstream.h \
    SourceCode/core/jsonutil/rapidjson/istreamwrapper.h \
    SourceCode/core/jsonutil/rapidjson/memorystream.h \
    SourceCode/core/jsonutil/rapidjson/ostreamwrapper.h \
    SourceCode/core/jsonutil/rapidjson/pointer.h \
    SourceCode/core/jsonutil/rapidjson/prettywriter.h \
    SourceCode/core/jsonutil/rapidjson/rapidjson.h \
    SourceCode/core/jsonutil/rapidjson/reader.h \
    SourceCode/core/jsonutil/rapidjson/schema.h \
    SourceCode/core/jsonutil/rapidjson/stringbuffer.h \
    SourceCode/core/jsonutil/json_utils.h \
    SourceCode/core/jsonutil/json_exception.h \
    SourceCode/core/request/iapi_request.h \
    SourceCode/core/request/i_api_finish_listener.h \
    SourceCode/core/network/http_connection.h \
    SourceCode/core/request/i_api_request_listener.h \
    SourceCode/core/request/request_utils.h \
    SourceCode/lazada/lazada_handler.h \
    SourceCode/lazada/dataitem/lazada_data_item_list_order.h \
    SourceCode/core/utils/api_command_defined.h \
    SourceCode/core/service_map_manager.h \
    SourceCode/core/request/apirequest_get.h \
    SourceCode/lazada/lazada_define.h \
    SourceCode/lazada/request/lazada_api_request_get.h \
    SourceCode/core/request/apirequest_worker.h \
    SourceCode/core/network/network_manager_factory.h \
    SourceCode/core/network/network_session_manager.h \
    SourceCode/gui/CustomControl/testingcellui.h \
    SourceCode/gui/CustomControl/sitemdelegate.h \
    SourceCode/gui/CustomControl/cache.h \
    SourceCode/gui/CustomControl/stableview.h \
    SourceCode/gui/CustomControl/sfilter-info.h \
    SourceCode/gui/CustomControl/flowlayout.h \
    SourceCode/gui/CustomControl/verticalscrollbar.h \
    SourceCode/lazada/lazada_request_api_factory.h \
    SourceCode/lazada/lazada_parser_factory.h \
    SourceCode/gui/CustomControl/detailwidget.h \
    SourceCode/uimodel.h \
    SourceCode/gui/CustomControl/sdialog.h \
    SourceCode/gui/CustomControl/svgwidget.h \
    SourceCode/lazada/lazada_api_command_defined.h \
    SourceCode/lazada/request/lazada_api_request_order_items.h \
    SourceCode/lazada/dataitem/lazada_data_item_order_items.h \
    SourceCode/lazada/dataitem/lazada_data_item_order.h \
    SourceCode/lazada/dataitem/lazada_data_item_bill_order.h \
    SourceCode/gui/table-model.h \
    SourceCode/ui_executor.h \
    SourceCode/gui/leftpanel.h \
    SourceCode/signalsender.h \
    SourceCode/gui/suserinfo.h \
    SourceCode/gui/CustomControl/drop-down-widget.h \
    SourceCode/gui/navigationbar.h \
    SourceCode/gui/CustomControl/page-ui-manager.h \
    SourceCode/gui/CustomControl/date-range-widget.h \
    SourceCode/lazada/request/lazada_api_request_set_status_to_canceled.h \
    SourceCode/lazada/request/lazada_api_request_set_status_to_packed_by_marketplace.h \
    SourceCode/lazada/request/lazada_api_request_set_status_to_ready_to_ship.h \
    SourceCode/lazada/request/lazada_api_request_set_invoice_number.h \
    SourceCode/lazada/request/lazada_api_request_get_failure_reasons.h \
    SourceCode/lazada/request/lazada_api_request_get_document.h \
    SourceCode/lazada/request/lazada_api_request_get_shipment_providers.h \
    SourceCode/lazada/request/lazada_api_request_get_metrics.h \
    SourceCode/lazada/request/lazada_api_request_get_payout_status.h \
    SourceCode/lazada/request/lazada_api_request_get_statistics.h \
    SourceCode/lazada/request/lazada_api_request_seller_update.h \
    SourceCode/lazada/request/lazada_api_request_user_update.h \
    SourceCode/lazada/request/lazada_api_request_get_category_attributes.h \
    SourceCode/lazada/request/lazada_api_request_get_category_tree.h \
    SourceCode/lazada/request/lazada_api_request_get_brands.h \
    SourceCode/lazada/request/lazada_api_request_remove_product.h \
    SourceCode/lazada/request/lazada_api_request_update_price_quantity.h \
    SourceCode/lazada/request/lazada_api_request_create_product.h \
    SourceCode/lazada/request/lazada_api_request_update_product.h \
    SourceCode/lazada/request/lazada_api_request_set_images.h \
    SourceCode/lazada/request/lazada_api_request_migrate_image.h \
    SourceCode/lazada/request/lazada_api_request_upload_image.h \
    SourceCode/lazada/request/lazada_api_request_search_spus.h \
    SourceCode/lazada/request/lazada_api_request_get_products.h \
    SourceCode/lazada/request/lazada_api_request_get_orders.h \
    SourceCode/lazada/request/lazada_api_request_get_order.h \
    SourceCode/gui/CustomControl/table/datahandler.h \
    SourceCode/gui/CustomControl/table/tinytablewidget.h \
    SourceCode/gui/CustomControl/table/tablecell.h \
    SourceCode/gui/CustomControl/horizontalscrollbar.h \
        SourceCode/gui/CustomControl/calendar-widget.h \
    SourceCode/gui/CustomControl/zbackground-menu.h \
    SourceCode/gui/CustomControl/background_menu_utils.h \

RESOURCES += \
    Resource/resource.qrc

DISTFILES += \
    Resource/Style/Generic/style.scss \
    Resource/Style/x100/style.scss \
    Resource/Style/Generic/_frameStyle.scss \
    Resource/Style/Generic/_labelStyle.scss


#kha test
