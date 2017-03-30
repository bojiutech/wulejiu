//网站插件部分
; (function ($) {
       if ($(window).height() > 875) {
            $(".bgBox").css({ "height": "100%" });
            }
    //depend on jquery 1.7.1.js、selector.js
    function Pagination(_this, opts) {
        this.opts = opts;
        this.$el = $(_this);
        this.$pageGo = null; //垂直分页
        this.$pageInfo = null; //分页信息
        this.$numbers = null; /*分页容器*/
        this.numbersWidth = 0; //遮罩宽度
        this.$numbersUL = null; /*分页所在ul*/
        this.$lHandler = null;
        this.$rHandler = null;
        this.firstBtn = null;
        this.lastBtn = null;
        this.lis = null;
        this.leftArray = []; //各个li偏移相对0点值
        this.widthsArray = []; //各个li的宽度
        this.totalWidth = 0; //所有li的宽度
        this.available = 0; 	//可移动距离
        this.index = 0; 		//当前li index指针,用于指定当前所在widthsArray中哪一项
        this.maxIndex = 0; 	//最大li index指针值
        this.centerNum = 0; 	//分页可视区域中间li
        this.lastClick = 0; 	//上一次点击的li index值
        this.currentClick = 0; //当前点击的li index值(index值有可能发生改变)
        this.currentPage = -1; 	//当前所在分页
        this.totalPage = 0; //总页数
        this.init();
    }
    Pagination.prototype = {
        init: function () {
            var self = this;
            var opts = self.opts;
            self.centerNum = 2;
            self.$numbers = self.$el.find(opts.classes.numbers);
            self.$numbersUL = self.$numbers.find('ul');
            //操作分页
            self.$lis = self.$numbersUL.find('li');
            self.$lHandler = self.$el.find(opts.classes.prev);
            self.$rHandler = self.$el.find(opts.classes.next);
            self.firstBtn = self.$el.find(opts.classes.first);
            self.lastBtn = self.$el.find(opts.classes.last);
            self.numbersWidth = self.$numbers.width();
            self.totalWidth = self.getWidths();
            self.totalPage = self.$lis.length;
            self.currentPage = -1;
            //初始化移动项目
            self.available = self.totalWidth - self.numbersWidth;
            self.maxIndex = self.getMaxIndex() + self.centerNum + 1;
            self.lastClick = self.centerNum;
            self.currentClick = self.centerNum;
            self._bindEvent();
        },
        _bindEvent: function () {
            var self = this;
            var opts = self.opts;
            var callback = opts.onActive;
            var curClass = opts.classes.cur.split('.')[1];
            self.$numbersUL.on('click', 'li', function (e) {
                var index = $(this).index();
                $(this).addClass(curClass).siblings().removeClass(curClass);
                self.flip(index);
                self.$el.trigger('page.click', self.currentPage + 1)
            });


            self.$lHandler.click(function () {
                if (self.currentPage >= 1) {
                    self.animateToRight(); //内容向右移动
                    self._flip(self.currentPage - 1);
                    self.$el.trigger('page.prev', self.currentPage + 1);
                }

            });

            self.$rHandler.click(function () {
                if (self.currentPage < self.totalPage - 1) {
                    self.animateToLeft(); //内容向左移动
                    self._flip(self.currentPage + 1);
                    self.$el.trigger('page.next', self.currentPage + 1);
                }

            });

            self.firstBtn.click(function () {
                self.$lis.first().addClass(curClass).siblings().removeClass(curClass);
                self.$numbersUL.animate({ marginLeft: 0 }, { duration: 100, complete: function () {
                } 
                });
                self.index = 0;
                self.lastClick = self.centerNum;

                self.flip(0); //翻页
            });
            self.lastBtn.click(function () {
                self.$lis.last().addClass(curClass).siblings().removeClass(curClass);
                self.$numbersUL.animate({ marginLeft: -self.countLeftAvaliableWidth() }, { duration: 1, complete: function () {
                    //console.log('ff');
                } 
                });
                self.lastClick = self.maxIndex;
                self.flip(self.totalPage - 1); //翻页
            });

        },
        animateToLeft: function () {
            var self = this;
            var step = self.widthsArray[self.index];
            var marginLeft = parseInt(self.$numbersUL.css('margin-left'));
            if (!!step && Math.abs(marginLeft) < Math.abs(self.available)) {
                self.$numbersUL.animate({ marginLeft: '-=' + step }, { duration: 100, complete: function () {
                } 
                });
                self.index++;
            }
        },
        animateToRight: function () {
            var self = this;
            var step;
            if (self.index > 0) step = self.widthsArray[--self.index];
            var marginLeft = parseInt(self.$numbersUL.css('margin-left'));
            if (!!step && marginLeft < 0) {
                self.$numbersUL.animate({ marginLeft: '+=' + step }, { duration: 100, complete: function () {
                } 
                });
            }
        },
        getWidths: function () {
            var self = this;
            var t = 0;
            self.totalWidth = 0;
            self.leftArray = [];
            self.widthsArray = [];

            self.$lis.each(function () {
                w = $(this).outerWidth(true);
                t += w;
                self.leftArray.push(t);
                self.widthsArray.push(w);
            });
            return t;
        },
        countWidthByIndex: function (index) {
            var self = this;
            var w = 0;
            while (index >= 0) {
                w += self.widthsArray[index];
                index--;
            }
            return w;
        },
        countLeftAvaliableWidth: function () {/*找到最后符合的li位置*/
            var self = this;
            var i = 0;
            var len = self.widthsArray.length;
            var w = 0;
            while (i < len) {
                self.index = i;
                if (w > Math.abs(self.available)) return w;
                w += self.widthsArray[i];
                i++;
            }
            return w;
        },
        getAvaliableMove: function (index) {
            var self = this;
            var w = 0;
            var i = 0;
            var marginLeft = Math.abs(parseInt(self.$numbersUL.css('margin-left')));
            while (i < index) {
                w = self.countWidthByIndex(i);
                if (w > Math.abs(self.available)) {
                    self.index = i + 1; //重定向self.index指针
                    return w;
                }
                i++;
            }
            return w;
        },
        getMaxIndex: function () {/*获得最大能移动的self.index值*/
            var self = this;
            var maxAvaliable = self.getAvaliableMove(self.widthsArray.length);
            self.index = 0;
            var i = 0;
            while (self.countWidthByIndex(i) < maxAvaliable) {
                i++;
            }
            return i;

        },
        flip: function (i, isReload) {
            var self = this;
            self.currentClick = i;
            var ot = 0;
            var indexOffset = 0;
            if (self.currentClick < self.centerNum) {
                self.currentClick = self.centerNum;
            } else if (self.currentClick > self.maxIndex) {
                self.currentClick = self.maxIndex;
            }
            if (self.currentClick > self.lastClick && self.currentClick > self.centerNum) {
                indexOffset = self.currentClick - self.lastClick; //self.index 指针偏移量
                self.index += indexOffset;
                ot = self.getAvaliableMove(self.index);
                self.$numbersUL.animate({ marginLeft: -ot }, { duration: 100, complete: function () { } });

            } else if (self.currentClick < self.lastClick) {
                indexOffset = self.currentClick - self.lastClick; //self.index 指针偏移量
                self.index += indexOffset;
                if (self.index <= 0) {
                    self.index = 0;
                    self.lastClick = self.currentClick;
                }
                ot = self.getAvaliableMove(self.index);
                self.$numbersUL.animate({ marginLeft: -ot }, { duration: 100, complete: function () { } });
            }
            self.lastClick = self.currentClick;

            self._flip(i, isReload); //翻页
        },
        _flip: function (i, isReload) {
            var self = this;
            var opts = self.opts;
            if (self.currentPage === i && !isReload) return false; //点击同一页不发生变化
            self.currentPage = i;
            self.$lis.eq(i).addClass('cur').siblings().removeClass('cur');
        }
    };


    $.fn.pagination = function (opt) {
        return $(this).each(function () {
            var handle = $(this).data('pagination_handle');
            if (!handle) {
                handle = new Pagination($(this), $.extend(true, {}, $.fn.pagination.defaults, opt));
                $(this).data('pagination_handle', handle);
            }
        });
    };
    $.fn.pagination.defaults = {
        classes: {
            cur: '.cur',
            prev: '.prev',
            next: '.next',
            first: '.first',
            last: '.last',
            numbers: '.nums'
        },
        speed: 100,
        curPage: 1, //当前所在页
        perPage: 4, //每页数据条数
        pageGo: false,
        pageInfo: false,
        pageNum: true,
        onSelected: null,
        //是否显示数字排
        showNumbers: true,
        //首页
        showFirst: true,
        //尾页
        showLast: true,
        //上一页
        showPrev: true,
        //下一页
        showNext: true,
        num: 3
    };
})(jQuery);
; (function ($) {
    //滚动条最小高度
    var BAR_MIN_HEIGHT = 20
    //滚动条占的宽度
		, BAR_WIDTH = 10
		, BAR_BG_OPACITY = .2
		, BAR_OPACITY = .4
    //滚动初始步长
		, DELTA_Y = 10
    //滚动步进速度
		, PLUS = 20
    //滚动方向
		, direction = 1;

    var VscrolBar = function ($content, conf) {
        //配置项
        this.conf = conf;
        //内容
        this.$content = $content;
        //滚动条
        this.$bar = null;
        this.barHeight = 0;
        //滚动组件背景
        this.$barBg = null;
        this.barBgHeight = 0;
        //滚动组件容器
        this.$barContainer = null;
        //鼠标是否在bar上按下
        this.isMouseDown = false;
        //上一次拖动的Y轴位置
        this.oldY = 0;
        //滚动bar当前position-top值
        this.curTop = 1;
        //Y轴滚动累计步长
        this.deltaYStep = 10;
        //显隐控制器
        this.visibleTimer = null;
        //鼠标是否在bar上
        this.onmouse = false;

        //滚动时执行的回调
        this.scrollFunc = null;

        //头部偏移值
        this.topFix = 1;
        //底部偏移值
        this.bottomFix = 1;

        //initialize
        this._init();
    };

    VscrolBar.prototype = {
        _init: function () {
            this.$barBg = $(this.conf.tmpl);
            this.$content.before(this.$barBg);
            this.$bar = this.$barBg.find('.scroll');
            this.barHeight = this.$bar.height();

            this.barBgHeight = this.$barBg.height();
            this.contentHeight = 0;

            this.curScrollTop = 0;

            this._initBar();
            this._events();
        },
        _initBar: function () {
            var ch = this.$content.height();
            this.contentHeight = ch;
            var sch = this._getScrollHeight() + 1000;
            //console.log(this.$content, sch, ch);
            if (sch > ch) {//&& this.$content.css('overflow-y') === 'auto'
                this.$barBg.show();
                this.$content.css('overflow-y', 'hidden');
                this.$bar.css({
                    'top': this.topFix
                });
            } else {
                this.$barBg.hide();
            }

        },
        _events: function () {
            var self = this;
            self.$bar.on('mousedown', function (e) {
                self.oldY = e.clientY;
                //console.log(self.$bar.position().top);
                self.curTop = self.$bar.position().top;

                //dragging
                $('body').on('mousemove', function (event) {
                    var distY = event.clientY - self.oldY;
                    self._slide(distY);
                    self.deltaYStep = self.$content.scrollTop();
                });
            }).on('mouseover', function () {
                self.onmouse = true;
            }).on('mouseout', function () {
                self.onmouse = false;
            });

            //mousewheel ing 
            self.$content.on('mousewheel', function (event) {
                var e = event.originalEvent;
                if ($(this).closest(':hidden').length) return;
                if (e.wheelDelta === 120) {
                    direction = -1;
                } else if (e.wheelDelta === -120) {
                    direction = 1;
                }
                var v = self.scrollTop() + (direction * PLUS);
                if (v < 0) {
                    v = 0;
                }
                self.scrollTop(v);
                return false;
            });

            self.$content.on('dom.change', function () {
                self.reload();
            });

            //stop dragging
            $('body').on('mouseup', function () {
                self.curTop = self.$bar.position().top;
                self.deltaYStep = DELTA_Y;
                $('body').off('mousemove');
                self.isMouseDown = false;
            });
        },
        _scrolling: function () {
            var self = this;

            //保存当前scrollTop值
            self.curScrollTop = self.$content.scrollTop();
        },
        _slide: function (distY) {
            var self = this;
            var ch = self.$content.height();
            var bh = self.$bar.height();
            var plusDist = distY + self.curTop;
            var bottom = this.barBgHeight - this.barHeight - this.bottomFix;
            var offset = 0; //用于滚动条的上下一像素偏差
            if (plusDist < this.topFix) {//0
                self.$bar.css('top', this.topFix);
                offset = -1;
            } else if (plusDist > bottom) {
                self.$bar.css('top', bottom);
                offset = 1;
            } else {
                self.$bar.css({ 'top': plusDist });
                offset = 0;
            }

            var percent = ((self.$bar.position().top + offset) / (ch - bh));
            self.$content.scrollTop((self._getScrollHeight() - ch) * percent);
        },
        _scrollTop: function (v) {
            //设置内容scrollTop
            this.$content.scrollTop(v);

            var st = this.$content.scrollTop();

            //取scrollTop最小值, 避免用户设置数值过大
            v = Math.min(st, v);

            var h = this.$content.height();
            //(内容区域scrollTop / 内容区域允许滚动的范围) * (滚动条允许滚动的范围)
            this.$bar.css('top', (v / (this._getScrollHeight() - h)) * ((h - (this.topFix + this.bottomFix)) - this.$bar.height()) + this.topFix);

            //滚动事件
            this._scrolling();

            //重新计算bar y轴偏移
            this.curTop = this.$bar.position().top;
        },
        _getScrollHeight: function () {
            return this.$content[0].scrollHeight;
        },
        scrollTop: function (v) {
            if ($.isNumeric(v)) {
                this._scrollTop(v);
                return this;
            } else {
                return this.$content.scrollTop();
            }
        },
        scrollToEnd: function () {
            this._scrollTop(this._getScrollHeight());
        },
        scrollToTop: function () {
            this._scrollTop(0);
        },
        reload: function () {

            //重新定位距离顶部距离
            this.curTop = 0;

            //重新初始化bar
            this._initBar();

            //恢复到reload之前的scrollTop值
            this.scrollTop(this.curScrollTop);

            //重置滚动速度,防止reset的时候累加
            self.deltaYStep = DELTA_Y;

            return this;
        },
        scroll: function (func) {
            if ($.isFunction(func)) {
                this.scrollFunc = func;
            }
        }
    };


    $.fn.vscrolBar = function () {
        return $(this).each(function () {
            var handle = $(this).data('vscroll_handle');
            if (!handle) {
                handle = new VscrolBar($(this), $.fn.vscrolBar.conf);
                $(this).data('vscroll_handle', handle);
            }
        });
    };
    $.fn.vscrolBar.conf = {
        tmpl: '<div class="scrollBg"><div class="scroll" style="top:1px;"></div></div>'
    };
})(jQuery);
; (function ($) {
    var Scroller = function (_this, opts) {
        this.$dom = $(_this);
        this.opts = opts;
        this.index = 0;
        this._init();
    };
    Scroller.prototype = {
        _init: function () {
            var self = this;
            var $items, $slider, $sliderItems, sliderId, sliderItemType, activeClass = 'cur';
            this.leftBtn = this.$dom.find(self.opts.leftBtn);
            this.rightBtn = this.$dom.find(self.opts.rightBtn);
            this.scrollPanel = this.$dom.find(self.opts.panel);
            sliderId = this.$dom.data('slider');
            if (sliderId) {
                $slider = $(sliderId);
                sliderItemType = $slider.data('itemtype');
                if (sliderItemType) $sliderItems = $slider.find(sliderItemType);
                if ($slider.data('active')) activeClass = $slider.data('active');
                if ($sliderItems) {
                    $slider.on('click', sliderItemType, function () {
                        $(this).addClass(activeClass).siblings(sliderItemType).removeClass(activeClass);
                        self.index = $(this).index();
                        self.scrollPanel.animate({ marginLeft: -self.step * self.index }, 300);
                    });
                }
            }
            $items = this.scrollPanel.find(this.scrollPanel.data('itemtype'));

            this.step = $items.eq(0).outerWidth(true);
            this.scrollPanelWidth = $items.length * this.step;
            this.maskWidth = this.scrollPanel.parent().width();
            this.avaiableWidth = this.scrollPanelWidth - this.maskWidth;

            var slideCallback = function () {
                if ($slider && $slider[0]) {
                    $sliderItems.eq(self.index).addClass(activeClass).siblings(sliderItemType).removeClass(activeClass);
                }
            };

            this.leftBtn.click(function () {
                var left;
                if (self.avaiableWidth >= self.step) {
                    left = parseInt(self.scrollPanel.css('margin-left'));
                    if (left < 0 && !self.scrollPanel.is(':animated')) {
                        self.index--;
                        self.scrollPanel.animate({ marginLeft: '+=' + self.step }, 300);
                        slideCallback(left);
                    }
                }
            });
            this.rightBtn.click(function () {
                var left;
                if (self.avaiableWidth >= self.step) {
                    left = parseInt(self.scrollPanel.css('margin-left'));
                    if ((Math.abs(left) <= self.avaiableWidth - self.step) && !self.scrollPanel.is(':animated')) {
                        self.index++;
                        self.scrollPanel.animate({ marginLeft: '-=' + self.step }, 300);
                        slideCallback(left);
                    }
                }
            });
        }
    }
    $.fn.scroller = function (opts) {
        return $(this).each(function () {
            var handle = $(this).data('scroller_handle');
            if (!handle) {
                handle = new Scroller($(this), $.extend(true, {}, $.fn.scroller.def, opts));
                $(this).data('scroller_handle', handle);
            }
        });
    };
    $.fn.scroller.def = {
        leftBtn: '.leftBtnTrigger',
        rightBtn: '.rightBtnTrigger',
        panel: '.scrollPanelTrigger'
    }
})(jQuery);

//网站逻辑部分
$(function () {
    var gIntervalTimer;
    //更新/初始化组件
    var gUpdatePlus = function () {
        if ($.fn.vscrolBar) {
            //初始化滚动条组件
            $('.vscrollTrigger').vscrolBar().each(function () {
                var v = $(this).data('vscroll_handle');
                if (v) v.reload();
            });
        }
        if ($.fn.pagination) {
            //初始化分页组件
            $('.paginationTrigger').pagination({
                classes: { prev: '.pagePrevTrigger', next: '.pageNextTrigger' }
            }).each(function () {
                var p = $(this).data('pagination_handle');
                if (p) p.flip(0);
            });
        }
    };
    //tab模块统一处理`
    var gTabModuleInit = function () {
        var $tab = $('.tabTrigger');
        var $tabContainer = $tab.find('.tabContainerTrigger');
        var $tabPage = $tab.find('.tabPageTrigger');
        var $pageNums = $tabPage.find('.pageNumTrigger');
        var total = $tabPage.data('total');
        var tabContainerStep = $tabContainer.data('step');
        $tabPage.data('page', 1); //设置默认第一页
        var gotoPage = function (i) {
            i--;
            $tabContainer.animate({ "margin-left": (-1 * i * tabContainerStep) }, 300);
        };

        $tabPage.off('page.prev').on('page.prev', function (e, v) {
            var page = $tabPage.data('page');
            if (page > 1) {
                page--;
                gotoPage(page);
                $tabPage.data('page', page);
            }
        });
        $tabPage.off('page.next').on('page.next', function (e, v) {
            var page = $tabPage.data('page');
            if (page < total) {
                page++;
                gotoPage(page);
                $tabPage.data('page', page);
            }
        });
        $tabPage.off('page.click').on('page.click', function (e, v) {
            $tabPage.data('page', v);
            gotoPage($tabPage.data('page'));
        });
    };

    /*********** 公共方法 start**************/
    // val为经json直接序列化后的C#的DateTime类型的数据
    function formatTime(val) {
        var re = /-?\d+/;
        var m = re.exec(val);
        var d = new Date(parseInt(m[0]));
        // 按【2012-02-13 09:09:09】的格式返回日期
        return d.format("yyyy-MM-dd");
    }
    // 用于格式化日期显示
    Date.prototype.format = function (format) //author: meizz 
    {
        var o = {
            "M+": this.getMonth() + 1, //month 
            "d+": this.getDate(),    //day 
            "h+": this.getHours(),   //hour 
            "m+": this.getMinutes(), //minute 
            "s+": this.getSeconds(), //second 
            "q+": Math.floor((this.getMonth() + 3) / 3),  //quarter 
            "S": this.getMilliseconds() //millisecond 
        }
        if (/(y+)/.test(format)) format = format.replace(RegExp.$1,
    (this.getFullYear() + "").substr(4 - RegExp.$1.length));
        for (var k in o) if (new RegExp("(" + k + ")").test(format))
            format = format.replace(RegExp.$1,
      RegExp.$1.length == 1 ? o[k] :
        ("00" + o[k]).substr(("" + o[k]).length));
        return format;
    }
    /*********** 公共方法 end**************/

    /*********** 弹出层模块  start***********/
    var popupCallbacks = {
        '#punishPopup': {
            show: function (_id) {
                $.ajax({
                    url: '/Home/PunishList/1',
                    success: function (data) {
                        indexModule.punishPopupInit(data);
                    }
                })
            }
        }
    };
    var popup = {
        mask: $('#mask'),
        show: function (trigger) {
            var _id = $(trigger).data('popup');
            $(_id).show();
            this.mask.show();
            if (popupCallbacks[_id] && $.isFunction(popupCallbacks[_id].show)) {
                popupCallbacks[_id].show.call(popupCallbacks[_id], _id);
            }
        },
        hide: function (trigger) {
            $(trigger).closest('.popup').hide();
            this.mask.hide();
        },
        init: function () {
            $('.popupCloseTrigger').click(function () {
                popup.hide(this);
            });
            $('.popupBtntrigger').click(function () {
                popup.show(this);
            });
        }
    }
    popup.init();

    /*********** 弹出层模块  end***********/

    /*********** 滚动模块  start***********/
    if ($.fn.scroller) $('.scrollerTrigger').scroller();
    /*********** 滚动模块  end***********/

    //主导航
    $('#mainNav').find('li:not(.cur)').hover(function () {
        $(this).addClass('hover');
    }, function () {
        $(this).removeClass('hover');
    });

    //电视台
    $('#tvNav').find('li').hover(function () {
        $(this).addClass('hover');
        var $b = $(this).find('b');
        var step = 1;
        gIntervalTimer = setInterval(function () {
            var left = parseInt($b.css('left'));
            if (left >= 70) left = -20;
            $b.css('left', (left + step + 'px'));
        }, 10);
    }, function () {
        $(this).removeClass('hover');
        if (gIntervalTimer) clearInterval(gIntervalTimer);
    });

    /*************** 主页  start***************/
    var indexModule = {};
    //图片滑动
    indexModule.sliderPicInit = function () {
        var $btnTriggers = $('#adBtnsTrigger > li');
        var $picsTrigger = $('#adPicsTrigger');
        var adIndex = 0;
        var step = $picsTrigger.find('li').eq(0).width();
        var total = $btnTriggers.length;
        var lock = false;
        $btnTriggers.click(function () {
            $(this).addClass('cur').siblings('li').removeClass('cur');
            adIndex = $(this).index();
            lock = true;
            $picsTrigger.animate({ "margin-left": (-1 * $(this).index() * step) }, 600, 'linear', function () {
                lock = false;
            });
        });

        setInterval(function () {
            adIndex = ++adIndex % total;
            if (!lock) $picsTrigger.animate({ "margin-left": (-1 * adIndex * step) }, 600, 'linear', function () {
                $btnTriggers.eq(adIndex).addClass('cur').siblings('li').removeClass('cur');
            });
        }, 4000);
    };

    //处罚公告
    indexModule.punishPopupInit = function (data) {
        var $punishTbody = $('#punishTbody');
        var $punishCurPage = $('#punishCurPage');
        var $punishPerPage = $('#punishPerPage');
        var punishTotalSize = data.TotalSize;
        var renderHtml = function (data, curPage) {
            $punishCurPage.html(curPage);
            $punishPerPage.html(punishTotalSize);
            $punishTbody.find("tr").remove();
            $.each(data, function (i, item) {
                $punishTbody.append("<tr><td>" + item.Name + "</td><td>" + formatTime(item.CreateDate) + "</td><td>" + item.PunishReason + "</td><td>" + item.PunishGame + "</td><td>" + item.PunishResult + "</td><td>" + item.PunishDeadline + "</td><td>" + item.PunishReopen + "</td><td>1</td></tr>");
            });
        };
        var renderHtmlSingle = function (data) {
            $punishCurPage.html(1);
            $punishPerPage.html(punishTotalSize);
            $punishTbody.find("tr").remove();
            if (data.Name != undefined) {
                $punishTbody.append("<tr><td>" + data.Name + "</td><td>" + formatTime(data.CreateDate) + "</td><td>" + data.PunishReason + "</td><td>" + data.PunishGame + "</td><td>" + data.PunishResult + "</td><td>" + data.PunishDeadline + "</td><td>" + data.PunishReopen + "</td><td>1</td></tr>");
            }
        };

        $punishTbody.data('page', 1);
        renderHtml(data.List);

        //搜索
        $('#punishSearch').click(function () {
            var username = $('#punishUsername').val();
            if (!!username && $.trim(username) != '') {
                username = $.trim(username);
                $.ajax({
                    url: '/Home/Punish/' + username,
                    success: function (data) {
                        renderHtmlSingle(data);
                        $punishTbody.data('page', 1);
                    }
                });
            }
            else {
                $.ajax({
                    url: '/Home/PunishList/1',
                    success: function (data) {
                        renderHtml(data.List, 1);
                        $punishTbody.data('page', 1);
                    }
                });
            }
        });
        //第一页
        $('#punishFirstPage').click(function () {
            $.ajax({
                url: '/Home/PunishList/1',
                success: function (data) {
                    renderHtml(data.List, 1);
                    $punishTbody.data('page', 1);
                }
            });
        });
        //最后一页
        $('#punishLastPage').click(function () {
            $.ajax({
                url: '/Home/PunishList/' + punishTotalSize,
                success: function (data) {
                    renderHtml(data.List, punishTotalSize);
                    $punishTbody.data('page', punishTotalSize);
                }
            });
        });
        //上一页
        $('#punishPrevPage').click(function () {
            var curPage = $punishTbody.data('page');
            curPage -= 1;
            if (curPage < 1)
                return;
            $.ajax({
                url: '/Home/PunishList/' + curPage,
                success: function (data) {
                    renderHtml(data.List, curPage);
                    $punishTbody.data('page', curPage); ///
                }
            });
        });
        //下一页
        $('#punishNextPage').click(function () {
            var curPage = $punishTbody.data('page');
            curPage += 1;
            if (curPage > punishTotalSize)
                return;
            $.ajax({
                url: '/Home/PunishList/' + curPage,
                success: function (data) {
                    renderHtml(data.List, curPage);
                    $punishTbody.data('page', curPage); ///
                }
            });
        });
        //跳转页
        $('#punishPageGoBtn').click(function () {
            var pageNum = $('#punishPageGoIpt').val();
            if (!!pageNum) {
                pageNum *= 1;
            }
            pageNum = pageNum > punishTotalSize ? punishTotalSize : pageNum;
            if ($.isNumeric(pageNum)) {
                $.ajax({
                    url: '/Home/PunishList/' + pageNum,
                    success: function (data) {
                        renderHtml(data.List, pageNum);
                        $punishTbody.data('page', pageNum); ///
                    }
                });
            }
        });
    };

    indexModule.sliderPicInit();


    /*************** 主页  end***************/


    /*************** 引导页 start***************/
    guideModule = {};
    //下载按钮动画
    //    guideModule.downHallInit = function () {
    //        $('#downHall').hover(function () {
    //            var $that = $(this);
    //            var step = 220;
    //            var posx = 0;
    //            gIntervalTimer = setInterval(function () {
    //                if (posx > -1980) {
    //                    posx = posx - step;
    //                } else {
    //                    posx = 0;
    //                }
    //                $that.css('background-position', posx + 'px 0');
    //            }, 100);
    //        }, function () {
    //            if (gIntervalTimer) clearInterval(gIntervalTimer);
    //            $(this).css('background-position', '0 0');
    //        });
    //    };
    //飘白云
    guideModule.cloudInit = function () {
        var Floater = function (dom, xRange, yRange, toward) {
            var self = this;
            this.$dom = $(dom);
            this.width = this.$dom.width();
            this.toward = toward || 1;
            var o = {
                top: Math.round(Math.random() * yRange),
                left: Math.round(Math.random() * xRange),
                speed: Math.round(Math.random() * 3) || 1
            };

            this.$dom.css({ top: o.top, left: o.left });
            this.intervalTimer = setInterval(function () {
                var left = parseInt(self.$dom.css('left'));
                left += (o.speed * self.toward);
                if (self.toward > 0) {
                    if (left >= xRange) {
                        self.$dom.css({ left: -(self.width - 40) });
                    } else {
                        self.$dom.css({ left: left });
                    }
                } else {
                    if (left <= -(self.width - 40)) {
                        self.$dom.css({ left: xRange });
                    } else {
                        self.$dom.css({ left: left });
                    }
                }
            }, 20);
        }
        var w = $(window).width();
        $('.floatsTrigger').each(function () {
            new Floater(this, w, 200, -1);
        });
    }
    guideModule.cloudInit();
    //guideModule.downHallInit();
    /*************** 引导页 end***************/

    /*************** 玩家排行页 start***************/
    playerRankModule = {};
    playerRankModule.rankNavInit = function () {
        //请求排行游戏数据
        $('#rankNav').on('click', 'a', function () {
            $(this).parent().addClass('cur').siblings().removeClass('cur');
            var href = "/Game/RankPartial/" + $(this).data('class');
            $.ajax({
                url: href,
                success: function (data) {
                    $('#rankBody').find('div').remove();
                    $('#rankBody').append(data); ///取得游戏排行类型数据
                    playerRankModule.rankBodyInit(); ///
                }
            });
            return false;
        });
        $('#rankNav').find('a').first().click();
    };

    playerRankModule.rankBodyInit = function () {
        var $tab = $('#rankGamesTab');
        var $tabContainer = $tab.find('.tabContainerTrigger');
        var $playerRankContent = $('#playerRankContent'); //table
        var renderHtml = function (data) {
            $playerRankContent.find("tr").remove();
            $.each(data, function (i, item) {
                if ((i % 2) == 0) {
                    $playerRankContent.append("<tr></tr>")
                    $playerRankContent.find("tr").last().append("<td class='textC'>" + item.Index + "</td><td class='textL'>" + item.Name + "</td><td class='dividing pr25'>" + item.Point + "</td>");
                }
                if ((i % 2) == 1) {
                    $playerRankContent.find("tr").last().append("<td class='textC'>" + item.Index + "</td><td class='textL'>" + item.Name + "</td><td class='pr25'>" + item.Point + "</td>");
                }
            });
        }

        //请求玩家排行数据
        $tabContainer.on('click', 'a', function () {
            $(this).closest('.tabContainerTrigger').find('li').removeClass('cur');
            $(this).closest('li').addClass('cur');
            var href = $(this).attr('href');
            $.ajax({
                url: href,
                success: function (data) {
                    renderHtml(data);
                }
            });
            return false;
        });
        $tabContainer.find('a').first().click();
        gTabModuleInit();
        gUpdatePlus();
    };
    playerRankModule.rankBodyInit();
    playerRankModule.rankNavInit();

    /*************** 玩家排行页 end ***************/

    /*************** 新手帮助页 start***************/
    var helpModule = {}
    helpModule.helpNavInit = function () {
        $('#helpNav').on('click', 'a', function () {
            var helf = $(this).attr('href');
            $(this).parent().addClass('cur').siblings().removeClass('cur');
            var href = "/Home/HelpPartial/" + $(this).data('class');
            $.ajax({
                url: href,
                success: function (data) {
                    $('#helpContainer').find('div').remove();
                    $('#helpContainer').append(data);
                    helpModule.tabInit();
                }
            });
            return false;
        });
        $('#helpNav').find('a').first().click();
    };
    helpModule.tabInit = function () {
        var $tab = $('#helpTutorialTab');
        var $tabContainer = $tab.find('.tabContainerTrigger');
        var $helpContent = $('#helpContent');

        $tabContainer.on('click', 'a', function () {
            $(this).closest('.tabContainerTrigger').find('li').removeClass('cur');
            $(this).closest('li').addClass('cur');
            var href = $(this).attr('href');
            $.ajax({
                url: href,
                success: function (data) {
                    $('.vscrollTrigger').vscrolBar().each(function () {
                        var v = $(this).data('vscroll_handle');
                        if (v) v.reload();
                    });
                    $helpContent.html(data.Content); ///
                }
            });
            return false;
        });
        $tabContainer.find('a').first().click();
        gTabModuleInit();
        gUpdatePlus();
    };
    helpModule.helpNavInit();
    helpModule.tabInit();
    /*************** 新手帮助页 end***************/

    /*************** 游戏页 start***************/
    var gameIntroModule = {}
    gameIntroModule.init = function () {
        $gameIntroContent = $('#gameIntroContent');
        $gameIntroContainer = $('#gameIntroContainer');
        $('#gameIntroTab').on('click', 'li', function () {
            $(this).addClass('cur').siblings().removeClass('cur');
            var href = "/Game/GameListPartial/" + $(this).data('class');
            $.ajax({
                url: href,
                success: function (data) {
                    $gameIntroContainer.html(data); ///
                    if ($.fn.scroller) $('.scrollerTrigger').scroller();
                    if (window.fixPng) {
                        fixPng();
                    }
                }
            })
        });
        $('#gameIntroTab').find('a').eq(2).click();
    };
    gameIntroModule.init();
    /*************** 游戏页 end***************/

    /*************** 电视台 start***************/
    var tvIntroModule = {}
    tvIntroModule.init = function () {
        $tvIntroContainer = $('#tvIntroContainer');
        $('#tvcooperationNav').on('click', 'li', function () {
            $('#tvcooperationNav li').removeClass('cur');
            $(this).addClass('cur');
            var href = "/Match/TvStationPartial/" + $(this).data('id');
            $.ajax({
                url: href,
                success: function (data) {
                    $tvIntroContainer.html(data); ///
                    tvIntroModule.loadVideo();
                }
            })
        });
        $('#tvcooperationNav').find('li').eq(0).click();
    };
    tvIntroModule.loadVideo = function () {
        $tvVideoContainer = $('#tvVideoContainer');
        var href = "/Match/TvVideoPartial/" + $tvVideoContainer.data('id');
        $.ajax({
            url: href,
            success: function (data) {
                $tvVideoContainer.html(data); ///
                if ($.fn.scroller) $('.scrollerTrigger').scroller();
                if (window.fixPng) {
                    fixPng();
                }
            }
        });
    };
    tvIntroModule.init();
    /*************** 游戏页 end***************/

    /*************** 新闻页 start***************/
    var newsModule = {}
    newsModule.tabInit = function () {
        var $newsTab = $('#newsTab');
        var $newsContent = $('#newsContent');
        var $tabContainerTrigger = $newsTab.find('.tabContainerTrigger');

        $tabContainerTrigger.on('click', 'a', function () {
            $(this).closest('.tabContainerTrigger').find('li').removeClass('cur');
            $(this).closest('li').addClass('cur');
            var href = $(this).attr('href');
            $.ajax({
                url: href,
                success: function (data) {
                    $('#noticetime').html(formatTime(data.CreateDate));
                    $newsContent.html(data.Content);
                    $('.vscrollTrigger').vscrolBar().each(function () {
                        var v = $(this).data('vscroll_handle');
                        if (v) v.reload();
                    });
                }
            });
            return false;
        });

        var exp = /\d+$/;
        var nid = window.location.href.match(exp);
        if (nid != null && !isNaN(nid)) {
            $tabContainerTrigger.find('a:[id="news_' + nid + '"]').click();
        }
        else
            $tabContainerTrigger.find('a').first().click();
        gTabModuleInit();
        gUpdatePlus();
    };
    newsModule.tabInit();
    /*************** 新闻页 end***************/

    /*************** 活动页 start***************/
    var gameActivityModule = {}
    gameActivityModule.init = function () {
        $activityAdvertisement = $('#activityAdvertisement');
        $activityGallery = $('#activityGallery');
        var renderHtml = function (data) {
            $activityAdvertisement.html('');
            $activityAdvertisement.append("<div class='img'><a href='" + data.Url + "' target='_blank'><img src='http://www.gameabc.com/Content/uploadImages/actionImages/" + data.BigImg + "'></a></div>");
            $activityAdvertisement.append("<div class='activityInfo'><ul><li><i></i></li><li><h4>" + data.Name + "(" + formatTime(data.StartTime) + "---" + formatTime(data.EndTime) + ")</h4><p>" + data.Remark + "</p></li></ul></div>");
        }
        $('#activityGallery').on('click', 'li', function () {
            var href = "/Activity/ActivityDetail/" + $(this).data('id');
            $.ajax({
                url: href,
                success: function (data) {
                    renderHtml(data); ///                    
                }
            })
            return false;
        });
        $('#activityGallery').find('a').first().click();
    };
    gameActivityModule.init();
    /*************** 活动页 end***************/

    /*************** 日志管理 start***************/
    var gameLogModule = {}
    gameLogModule.init = function () {
        $('.downLog').bind('click', function () {
            var href = "/Log/LobbyDownLog/" + $(this).data('name');
            $.ajax({
                url: href,
                type: 'POST',
                data: { 'r': Math.random },
                success: function () {
                }
            })
        });
    };
    gameLogModule.init();
    /*************** 日志管理 end***************/

});