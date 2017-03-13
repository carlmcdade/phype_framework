(function($) { 
  $(document).ready(function() {
	  
	//create an ajaxmanager named menuAjaxControl 
	$.manageAjax.create('menuControl', { 
		  queue: true, 
		  cacheResponse: true 
	});
	
	
  	var item = '#main-menu li a';
  	var http_addy = '../';
  	$('.navigation').prepend('<div class="vocabulary"><div id="term-nodes"></div></div>');
  	
  	// vocabulary id is set in the menu. If one is found then load the terms to the menu
  	     $('[id^=vocabulary-]').each(function(event) {
  			
  				var voc_id = $(this).attr('id').split('-');
  				var voc_con = $(this).attr('id');
				
  				$.manageAjax.add('menuControl', { 
					success: function(html) { 
						$('.navigation').children('.vocabulary').append(html); 
						}, 
					url: http_addy + '?q=category/content/term_list/' + voc_id[1] + '/' + voc_id[2]
				});
											
		 });
	     $('[id^=shop-]').each(function(event) {
  			
  				var voc_id = $(this).attr('id').split('-');
  				var voc_con = $(this).attr('id');
  				 				
				$.get(http_addy + '?q=category/content/term_list/' + voc_id[1] + '/' + voc_id[2], function(data) {
						$('.navigation').children('.vocabulary').append(data);
				});
											
		 });
		 
		 
	

  	// use this to get the terms nodes
		$(".term a").live("mouseover click", function(event){
				event.preventDefault();
				
		        var parenta = $(this);
		        var pair_id = $(this).attr('id');
				
				$('.activity-indicator').remove();
				$(this).append('<span class="activity-indicator"></span>');			
				
                
    			$('#term-nodes').show();
    			$('#term-nodes').html($('#' + pair_id + '-nodes').html());
    			$(parenta).children('.activity-indicator').remove();
    						
				          
		});
		
		// Shows the terms and container for this vocabulary
		 
		$('[id^=vocabulary-],[id^=shop-]').mouseenter(
		   		    		
			function() {
				
			    var voc_id = $(this).attr('id').split('-');
				var child_id = $(this).attr('id').split('-');
				var first_term = $('#voc-'+ child_id[1] + " div:first-child").attr('id').split('-');
				
				$('.vocabulary').show();
				$('.vocabulary').children().hide();
				$('.vocabulary').children('#voc-'+ child_id[1]).show();			
				
				$('#term-nodes').show();
				$('#term-nodes').html($('#term-' + first_term[1] + '-nodes').html()); 				
				
			}
		);
		
		$('.navigation').mouseleave(
			function() {
				
				$('.navigation').children('.vocabulary').hide();
                $('#main-menu li a').removeClass('link-active');
			}
		);

        $('#main-menu li a').mouseenter(
			function(event) {
				
                $('#main-menu li a').removeClass('link-active');
				$(this).addClass('link-active');
			}
		);

		
    // the shop area containers load into the menu
	// vocabulary id is set in the menu. If one is found then load the terms to the menu
  	    $('*[id*=shop]:visible').click(function() {
  				var shop_id = $(this).attr('id').split('-');
  				var parent_li = $(this).parent('[class^=menu-]');
				
		 });
	// featured content
	
	// load the first item
	  $('#featured-content').append('<div id="featured-content-viewer"></div>');
	  var first = $('.jcarousel-view--featured--featured-block .jcarousel-item-1').children('.features').html();
	  $('#featured-content-viewer').html(first);
	  
	  // load the others on hover
	  $('.jcarousel-view--featured--featured-block li').children('a').hover(function(event){
	  		  var feature = $(this).next('.features').html();
	  		  event.preventDefault();
			  $('#featured-content-viewer').html(feature);
	  
	  });
    }); 
})(jQuery);
