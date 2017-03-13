<!DOCTYPE html>
<html lang="en">
<head>

	<meta charset="utf-8">
	<title>FHQK Universal | Pay What You Want for CCK</title>
	<meta name="description" content="">
	<meta name="author" content="">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="http://universal.fhqk.com/css/normalize.css">
	<link rel="stylesheet" href="http://universal.fhqk.com/css/skeleton.css">
    <link rel="stylesheet" href="http://cck.fhqk.com/site/site.css">
	<link rel="icon" type="image/png" href="http://universal.fhqk.com/images/favicon.png">

</head>
<body>
<div id="header" class="row">
    <div class="sixteen columns"><h1 class="head-title"><span>The Content Connection Kit</span><br /><span>is freedom.</span></h1></div>
</div>
<div id="root-content" class="container">

    <div class="row">

        <div class="one-half column">
            <h2 class="">Here's what you get</h2>
            <p>Entrepreneurs make many choices based on the initial start-up costs. When faced
                with the reality of starting a business on little or no budget getting something for free
                might seem like a good thing. But free can also mean giving up your freedom.</p>

            <p>Choosing a php framework or content management system is an investment in time and money. CCK will free you from the high costs of building a quality web space.
            Most of all CCK gives you the freedom to be small and independent of enterprise software. </p>

            <p>It is a good possibility that you are a web developer or agency looking for a web site building platform to present for an existing or future client. CCK will free
            you from the chains of copy left licensing. Create and sell whatever you like to build a solid business foundation. Protect
            your <b>competitive advantage</b> while <em>legally distributing products</em> and delivering services.</p>

            <p>Get more truly useful building blocks with flexibility. CCK does not provide the needless complexities of buzzword
            programming. What you get is a clean understandable framework for adding in those items if you feel your projects
            needs them.</p>

            <a href="http://cck.fhqk.com/index.php?">Tour the demo</a> | <a href="http://blog.fhqk.com">Read more</a>
        </div>
        <div class="one-half column">
            <h2 class="">What's it worth?</h2>
			<form id="pp" name="pp" action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_blank">

            <input type="hidden" name="cmd" value="_xclick">
            <input type="hidden" name="business" value="carlmcdade@gmail.com">

                <h2 id="price-container"><span>$</span><span id="price">150</span><sup>00</sup></h2>
                <div id="price-slider"><span id="plus">+</span><input type="range" min="0" max="140" value="0" step="1" oninput="showValue(this.value,'amount');" onchange="showValue(this.value,'amount');" /><span id="minus">-</span></div>

                <input type="hidden" name="no_shipping" value="0">
                <input type="hidden" name="no_note" value="1">
                <input type="hidden" name="currency_code" value="USD">
                <input type="hidden" name="lc" value="US">
                <input type="hidden" name="bn" value="PP-BuyNowBF">
                <input type="hidden" name="item_number" value="cck-2015-06-30">
                <input type="hidden" name="item_name" value="cck-single-user-license">
                <input value="150" id="amount" type="hidden" name="amount" readonly>
                <input type="hidden" name="return" value="http://cck.fhqk.com/site/payment-complete.php/">
                <div id="pay-button"><input type="submit" value="Pay with PayPal"></div>

            </form>
            <div class="pointer-spacer"></div>
            <div class="the-developer">
                <img id="the-dev" src="http://cck.fhqk.com/site/carl_n.jpg"/>
                <h3>The developer</h3>
                <p> Has been helping small businesses realize their internet space since 1997.</p>

            </div>
			<script type="text/javascript">
			function showValue(newValue,fieldname)
			{
                var x = document;
                var max_range = 150;
                newValue = max_range - newValue;
                x.pp[fieldname].value=newValue;
                document.getElementById('price').innerHTML = newValue;
			}
			</script><br />

		</div>

    </div>

</div>
</body>
</html>