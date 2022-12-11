$(document).ready(function () {
    $(".logo img").mouseover(function () {
        $(this).fadeOut(500, function () { $(this).fadeIn(1000); });
    });
});