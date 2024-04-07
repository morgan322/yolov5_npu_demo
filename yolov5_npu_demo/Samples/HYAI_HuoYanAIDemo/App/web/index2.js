function $id (id) {
	return document.getElementById(id);
}

var SPlayer = top.SPlayer;
var $videoWrap = $id('sdev_stream_wrap');

/*
* 创建视频相关的内容，是脱离其他任意环境的
* 所有任务开始之前，需要先创建一个实例
* 这个实例的创建不包含任何内容，仅仅是创建一个执行环境
* 无论视频相关的方法是否同步，都需要写成回调形式
* 基类需要内置发布订阅的内容，作为系统事件处理
*/


var state = {
	containerID: 0,
	player: null,
	Shape: null,
	exclusion_zone: {
                shapeId: null,
                data: null
            }
}

state.player = new SPlayer(this);


var delayBind = function () {
	$id('manualLogin').onclick = function () {
		var username = $id('username').value;
		var password = $id('password').value;
		var ip = $id('ip').value;
		var port = $id('port').value - 0;

		state.player.onVideoLogin(ip, port, username, password, loginSessedFn)
	}

	$id('autoLogin').onclick = function () {
		state.player.onVideoAutoLogin(loginSessedFn);
	}
}

state.player.onload(function (loadStatus) {
	console.log('loadStatus');
	// 将视频区域覆盖到div上
	state.player.refElements($videoWrap);

	// delayBind();
	
	state.player.onVideoAutoLogin(loginSessedFn);
	// state.player.onVideoLogin('172.27.4.117', 80, 'admin', 'admin123', loginSessedFn);
});

/*
* 整个页面离开时执行的函数
* 如果当前app没有其他副作用，那么这个函数可以不执行
* 
*/
state.player.onDestory(function () {
	console.log('pageDestroy');
});

function $id (id) {
	return document.getElementById(id);
}

function checkVersion (v) {
	var result = state.player.checkVersion('1.0.1');
	if (result === SPlayer.VERSION_UNMATCHED) {
		console.log('版本未捕获，可能太新了');
	} else if (result === SPlayer.VERSION_LOW) {
		console.log('版本太老了， 可以更新更新的程序');
	} else {
		console.log('版本匹配');
	}
	
}

// 初始化配置参数
function load_param() {
	var reqURL = "/DHOP_API/" + getAppName() + "/getConfig";
	$.ajax({
		url: reqURL,
		type: "get",
		dataType: "json",
		error: function (xhr) {
			console.log("失败了");
		},
		success: function (response, status, xhr) {
			console.log("获取成功");

			// response中的内容，格式见dhop_smp_web.c文件中的doGet函数
			console.log(response);

			// 设置加载参数后，显示排除区的信息
			state.exclusion_zone.data = response.exclusionZone;
			var data1 = {
				dataKey: response.exclusionZone
			}
			var polygonData = JSON.stringify(data1);
			state.Shape.CreateMainShape(state.containerID, 'Polygon', 'Polygon', 'dataKey', polygonData, '').done(function (shapeId) {
				state.exclusion_zone.shapeId = shapeId;
				state.Shape.SetShapeName(shapeId, "目标排除区");
			});
		}
	});
}

function getAppName() {
	var query = window.location.search;
	var i = 0;
	var n = query.search(/(\?|&)appName=/);
	if (n < 0) {
		return "";
	}
	n += 9;
	for (i = n; i < query.length; i++) {
		if (query[i] == '&' || query[i] == '?') {
			break;
		}
	}
	return query.slice(n, i);
}



function loginSessedFn (loginStatus) {
	console.log('loginStatus');
	var plugin = state.player._plugin;
	//var Shape = instance.Shape;
	state.Shape = state.player.Shape;

	checkVersion('1.0.1');

	state.Shape.CreateMainContainer().done(function (containerID) {
		state.containerID = containerID;
	});
	
	// 从设备中加载历史配置
	load_param();

	$id('CreateShape').onclick = function () {
		var mockData = JSON.stringify({
			dataKey: [
				[4109,1811],
				[6592,1947],
				[6067,4164],
				[3584,3712]
			]
		});
		
		state.Shape.DeleteShape(state.exclusion_zone.shapeId);

		// shapeType Polygon, Line, DetectLine(拌线)
		// 默认创建的图形，是不允许拖动的
		var shapeType = 'Polygon';
		state.Shape.CreateMainShape(state.containerID, 'EventName', shapeType, 'dataKey', '', {}).done(function (shapeId) {
			state.exclusion_zone.shapeId = shapeId;
			state.Shape.SetContainerTip(state.containerID, '请绘制');
		});
	}
	
	$id('SaveShape').onclick = function () {
		
		var param;
			state.Shape.GetShapeInfoData(state.exclusion_zone.shapeId).done(function (data) {
			param = JSON.stringify(data, null, 4);
			state.exclusion_zone.data = JSON.parse(data).dataKey;
	});
	console.log(param);
	
	var zone_data = {
                    exclusionZone: state.exclusion_zone.data
                }
	/*
	根据DHOP的APP与Web私有交互协议规范，发送到设备上。
	URL是/DHOP_API/<AppName>/<path>?<paramters>，如:
		/DHOP_API/Demo1/setConfig
		/DHOP_API/Demo1/setConfig?a=1&b=2&c=3
		/DHOP_API/Demo1/start
	*/
	var reqURL = "/DHOP_API/" + getAppName() + "/setParam";
	// 采用jquery的ajax模块
	$.ajax({
		url: reqURL,
		type: "post",
		dataType: "json",
		data: JSON.stringify(zone_data),  // 将json转成字符串，发送到APP
		error: function (xhr) {
			console.log("失败了");
		},
		success: function (response, status, xhr) {
			console.log("保存成功");
		}
	});
	console.log(param);
	
	}
	

	/*Enter: 0,
    Leave: 1,
    LeftToRight: 0,
    RightToLeft: 1,
    Both: 2*/

	/*$id('addTip').onclick = function () {
		var text = $id('shapeTipIpt').value;
		Shape.SetContainerTip(state.containerID, text);
	}*/

	$id('shapeIdSel').onchange = function () {
		state.exclusion_zone.shapeId = this.value;
	}
}