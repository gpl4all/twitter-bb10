/*
 * ApiResponse.cpp
 *
 *  Created on: Feb 18, 2012
 *      Author: Kyle
 */

#include "ApiResponse.h"
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtCore>
#include <bb/data/JsonDataAccess>

ApiResponse::ApiResponse(ApiResponseObjectFactory::ApiType targetType) {
	response = ApiResponseObjectFactory::createApiResponseObject(targetType);
	type = targetType;
}

ApiResponse::~ApiResponse() {
}

AbstractObjectBase* ApiResponse::getResponse() {
	return response;
}

ResponseMeta* ApiResponse::getMeta() {
	return meta;
}

ApiResponseObjectFactory::ApiType ApiResponse::getType() {
	return type;
}

void ApiResponse::parse(QByteArray data) {
	bool ok;
	bb::data::JsonDataAccess json;
	QVariant resp = json.loadFromBuffer(data);
	if(resp.canConvert(QVariant::List)) {
		foreach(const QVariant &var, resp.toList()) {
			qDebug() << var;
		}
	} else if(response != NULL && resp.canConvert(QVariant::Map)) {
		response->parse(resp.toMap());
	}
}
