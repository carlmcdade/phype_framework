<input id="menu-trigger" class="menu-trigger" type="checkbox" accesskey="m">
<label for="menu-trigger"></label>
<nav id="root_nav_wrap">

        <div class="forms-menu">
            <?php foreach($levels as $key => $parent){ ?>
                <span class="current-menu-item"><?php echo '' . $parent . ''; ?></span>
            <?php } ?>
            <div style="clear:both;width:100%;height:10px;"></div>
        </div>
        <div class="message">
            <?php echo (isset($content) ? $content : ''). "\n"; ?>
            <div style="clear:both;width:100%;height:10px;"></div>
        </div>
</nav>
