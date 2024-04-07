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
	exclusion_zone: [
		{
			shapeId: null,
			data: null
		},
		{
			shapeId: null,
			data: null
		},
		{
			shapeId: null,
			data: null
		},
		{
			shapeId: null,
			data: null
		}
	]
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
			// 暴露垃圾
			if (response.rubbish) {
				if (response.rubbish.exclusionZone && response.rubbish.exclusionZone.length) {
					state.exclusion_zone[0].data = response.rubbish.exclusionZone;
					var rubbishData = {
						dataKey: response.rubbish.exclusionZone
					}
					var rubbishPolygonData = JSON.stringify(rubbishData);
					state.Shape.CreateMainShape(state.containerID, 'Polygon', 'Polygon', 'dataKey', rubbishPolygonData, '').done(function (shapeId) {
						state.exclusion_zone[0].shapeId = shapeId;
						state.Shape.SetShapeName(shapeId, "暴露垃圾");
						state.Shape.DisableMainShape();
					});
				}
				$("#area1_timer1").val(response.rubbish.timer1);
				$("#area1_timer2").val(response.rubbish.timer2);
				$("#area1_level").val(response.rubbish.level);
				$("#area1_platform").val(response.rubbish.platform);
				$("[name='area1_voice'][value=" + response.rubbish.voice + "]").prop("checked", true);
				if (response.rubbish.voice == '1') {
					$("#area1_volume_group").show();
				}
				$("#area1_volume").val(response.rubbish.volume);
			}

			// 垃圾桶满溢
			if (response.overflow) {
				if (response.overflow.exclusionZone && response.overflow.exclusionZone.length) {
					state.exclusion_zone[1].data = response.overflow.exclusionZone;
					var overflowData = {
						dataKey: response.overflow.exclusionZone
					}
					var overflowPolygonData = JSON.stringify(overflowData);
					state.Shape.CreateMainShape(state.containerID, 'Polygon', 'Polygon', 'dataKey', overflowPolygonData, '').done(function (shapeId) {
						state.exclusion_zone[1].shapeId = shapeId;
						state.Shape.SetShapeName(shapeId, "垃圾桶满溢");
						state.Shape.DisableMainShape();
					});
				}
				$("#area2_timer1").val(response.overflow.timer1);
				$("#area2_timer2").val(response.overflow.timer2);
				$("#area2_level").val(response.overflow.level);
				$("#area2_platform").val(response.overflow.platform);
				$("[name='area2_voice'][value=" + response.overflow.voice + "]").prop("checked", true);
				if (response.overflow.voice == '1') {
					$("#area2_volume_group").show();
				}
				$("#area2_volume").val(response.overflow.volume);
			}

			// 厨余未破袋
			if (response.bag) {
				if (response.bag.exclusionZone && response.bag.exclusionZone.length) {
					state.exclusion_zone[2].data = response.bag.exclusionZone;
					var bagData = {
						dataKey: response.bag.exclusionZone
					}
					var bagPolygonData = JSON.stringify(bagData);
					state.Shape.CreateMainShape(state.containerID, 'Polygon', 'Polygon', 'dataKey', bagPolygonData, '').done(function (shapeId) {
						state.exclusion_zone[2].shapeId = shapeId;
						state.Shape.SetShapeName(shapeId, "厨余未破袋");
						state.Shape.DisableMainShape();
					});
				}
				$("#area3_timer1").val(response.bag.timer1);
				$("#area3_timer2").val(response.bag.timer2);
				$("#area3_level").val(response.bag.level);
				$("#area3_platform").val(response.bag.platform);
				$("[name='area3_voice'][value=" + response.bag.voice + "]").prop("checked", true);
				if (response.bag.voice == '1') {
					$("#area3_volume_group").show();
				}
				$("#area3_volume").val(response.bag.volume);
			}

			// 来人提醒
			if (response.person) {
				if (response.person.exclusionZone && response.person.exclusionZone.length) {
					state.exclusion_zone[3].data = response.person.exclusionZone;
					var personData = {
						dataKey: response.person.exclusionZone
					}
					var personPolygonData = JSON.stringify(personData);
					state.Shape.CreateMainShape(state.containerID, 'Polygon', 'Polygon', 'dataKey', personPolygonData, '').done(function (shapeId) {
						state.exclusion_zone[3].shapeId = shapeId;
						state.Shape.SetShapeName(shapeId, "来人提醒");
						state.Shape.DisableMainShape();
					});
				}
				$("#area4_timer1").val(response.person.timer1);
				$("#area4_timer2").val(response.person.timer2);
				$("#area4_level").val(response.person.level);
				$("#area4_platform").val(response.person.platform);
				$("[name='area4_voice'][value=" + response.person.voice + "]").prop("checked", true);
				if (response.person.voice == '1') {
					$("#area4_volume_group").show();
				}
				$("#area4_volume").val(response.person.volume);
			}

			// 督导员离岗
			if (response.worker) {
				$("#area5_timer1").val(response.worker.timer1);
				$("#area5_timer2").val(response.worker.timer2);
				$("#area5_level").val(response.worker.level);
				$("#area5_platform").val(response.worker.platform);
				$("[name='area5_voice'][value=" + response.worker.voice + "]").prop("checked", true);
				if (response.worker.voice == '1') {
					$("#area5_volume_group").show();
				}
				$("#area5_volume").val(response.worker.volume);
			}
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

	$id('CreateShape1').onclick = function () {
		var mockData = JSON.stringify({
			dataKey: [
				[4109,1811],
				[6592,1947],
				[6067,4164],
				[3584,3712]
			]
		});
		
		state.Shape.DeleteShape(state.exclusion_zone[0].shapeId);

		// shapeType Polygon, Line, DetectLine(拌线)
		// 默认创建的图形，是不允许拖动的
		var shapeType = 'Polygon';
		state.Shape.CreateMainShape(state.containerID, 'EventName', shapeType, 'dataKey', '', {}).done(function (shapeId) {
			state.exclusion_zone[0].shapeId = shapeId;
			state.Shape.SetContainerTip(state.containerID, '请绘制');
		});
	}

	$id('CreateShape2').onclick = function () {
		state.Shape.DeleteShape(state.exclusion_zone[1].shapeId);

		// shapeType Polygon, Line, DetectLine(拌线)
		// 默认创建的图形，是不允许拖动的
		var shapeType = 'Polygon';
		state.Shape.CreateMainShape(state.containerID, 'EventName', shapeType, 'dataKey', '', {}).done(function (shapeId) {
			state.exclusion_zone[1].shapeId = shapeId;
			state.Shape.SetContainerTip(state.containerID, '请绘制');
		});
	}

	$id('CreateShape3').onclick = function () {
		state.Shape.DeleteShape(state.exclusion_zone[2].shapeId);

		// shapeType Polygon, Line, DetectLine(拌线)
		// 默认创建的图形，是不允许拖动的
		var shapeType = 'Polygon';
		state.Shape.CreateMainShape(state.containerID, 'EventName', shapeType, 'dataKey', '', {}).done(function (shapeId) {
			state.exclusion_zone[2].shapeId = shapeId;
			state.Shape.SetContainerTip(state.containerID, '请绘制');
		});
	}

	$id('CreateShape4').onclick = function () {
		state.Shape.DeleteShape(state.exclusion_zone[3].shapeId);

		// shapeType Polygon, Line, DetectLine(拌线)
		// 默认创建的图形，是不允许拖动的
		var shapeType = 'Polygon';
		state.Shape.CreateMainShape(state.containerID, 'EventName', shapeType, 'dataKey', '', {}).done(function (shapeId) {
			state.exclusion_zone[3].shapeId = shapeId;
			state.Shape.SetContainerTip(state.containerID, '请绘制');
		});
	}
	
	$id('SaveShape').onclick = function () {
		this.disabled = "disabled";
		for (var i = 0; i < state.exclusion_zone.length; i++) {
			if (state.exclusion_zone[i].shapeId) {
				state.Shape.GetShapeInfoData(state.exclusion_zone[i].shapeId).done(function (data) {
					data = JSON.parse(data);
					state.exclusion_zone[i].data = data.dataKey;
				});
			}
		}
	
		var zone_data = {
			rubbish: {
				timer1: $("#area1_timer1").val(),
				timer2: $("#area1_timer2").val(),
				level: $("#area1_level").val(),
				platform: $("#area1_platform").val(),
				voice: $("[name='area1_voice']:checked").val(),
				volume: $("#area1_volume").val(),
				exclusionZone: state.exclusion_zone[0].data
			},
			overflow: {
				timer1: $("#area2_timer1").val(),
				timer2: $("#area2_timer2").val(),
				level: $("#area2_level").val(),
				platform: $("#area2_platform").val(),
				voice: $("[name='area2_voice']:checked").val(),
				volume: $("#area2_volume").val(),
				exclusionZone: state.exclusion_zone[1].data
			},
			bag: {
				timer1: $("#area3_timer1").val(),
				timer2: $("#area3_timer2").val(),
				level: $("#area3_level").val(),
				platform: $("#area3_platform").val(),
				voice: $("[name='area3_voice']:checked").val(),
				volume: $("#area3_volume").val(),
				exclusionZone: state.exclusion_zone[2].data
			},
			person: {
				timer1: $("#area4_timer1").val(),
				timer2: $("#area4_timer2").val(),
				level: $("#area4_level").val(),
				platform: $("#area4_platform").val(),
				voice: $("[name='area4_voice']:checked").val(),
				volume: $("#area4_volume").val(),
				exclusionZone: state.exclusion_zone[3].data
			},
			worker: {
				timer1: $("#area5_timer1").val(),
				timer2: $("#area5_timer2").val(),
				level: $("#area5_level").val(),
				platform: $("#area5_platform").val(),
				voice: $("[name='area5_voice']:checked").val(),
				volume: $("#area5_volume").val()
			}
        }
		console.log(zone_data);
		/*
		根据DHOP的APP与Web私有交互协议规范，发送到设备上。
		URL是/DHOP_API/<AppName>/<path>?<paramters>，如:
			/DHOP_API/Demo1/setConfig
			/DHOP_API/Demo1/setConfig?a=1&b=2&c=3
			/DHOP_API/Demo1/start
		*/
		var reqURL = "/DHOP_API/" + getAppName() + "/setParam";
		var _this = this;
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
			},
			complete: function() {
				_this.disabled = null;
			}
		});
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