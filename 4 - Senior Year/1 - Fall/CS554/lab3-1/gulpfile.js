var gulp = require('gulp');
var sass = require('gulp-sass');
var sourcemaps = require('gulp-sourcemaps');
var concat = require('gulp-concat');
var clean = require('gulp-clean-css');
var autoprefixer = require('gulp-autoprefixer');


gulp.task('styles', function() {
	return gulp.src('src/*.scss')
	.pipe(sass())
	.pipe(concat('all.css'))
	.pipe(clean())
	.pipe(autoprefixer())
	.pipe(sourcemaps.write())
	.pipe(gulp.dest('public/css'));
});